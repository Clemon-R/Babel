//
// Created by romain on 06/10/18.
//

#include "ClientManager.h"
#include <algorithm>
#include <client/src/forms/livewindow.h>
#include <client/src/network/ClientController.h>
#include <protocol/LoginMessage.h>
#include <client/src/sound/Microphone.hpp>
#include <client/src/sound/Speaker.hpp>
#include <client/src/codec/Opus.hpp>
#include "ui_livewindow.h"

ClientManager::ClientManager(LiveWindow *ui, const std::string &username, int &volumeSpeaker, int &volumeMicrophone)
        : _controller(new ClientController(this)),
          _serverConnector(*_controller),
          _hostConnector(*_controller),
          _server(*_controller),
          _locker(),
          _ui(ui),
          _username(username),
          _contacts(),
          _imHost(false),
          _isCalling(false),
          _volumeSpeaker(volumeSpeaker),
          _volumeMicrophone(volumeMicrophone),
          _listSamples()
{}

void ClientManager::startHost() {
    lock_t lock(_locker);
    static bool started = false;

    if (started) return;

    _server.run(true);
    started = true;
}

void ClientManager::closeAllClients() {
    lock_t lock(_locker);

    for (auto &keyset : _server.getClients()){
        NetworkClient *client = keyset.second.get();
        client->getSession()->getSocket().close();
    }
    _imHost = false;
}

void ClientManager::closeConnection() {
    lock_t lock(_locker);

	if (_hostConnector.getSession()->getSocket().is_open())
		_hostConnector.getSession()->getSocket().close();
}

void ClientManager::closeCall()
{
	if (_imHost)
		closeAllClients();
	else
		closeConnection();
}

void ClientManager::close()
{
	lock_t lock(_locker);

	if (_serverConnector.getSession()->getSocket().is_open())
		_serverConnector.getSession()->getSocket().close();
}


boost::uint16_t ClientManager::getPort() {
    lock_t lock(_locker);

    return _server.getPort();
}

void ClientManager::connectToServer(std::string const &host, uint16_t port) {
    lock_t lock(_locker);

    _serverConnector.connect(host, port, true);
}

void ClientManager::connectToHost(std::string const &host, uint16_t port) {
    lock_t lock(_locker);

    _hostConnector.connect(host, port, true);
}

void ClientManager::addContact(std::string const &contact) {
    lock_t lock(_locker);

    _contacts.push_back(contact);
    _ui->insertListData(contact);
}

void ClientManager::delContact(std::string const &contact) {
    lock_t lock(_locker);

    std::remove_if(_contacts.begin(),_contacts.end(), [&contact](std::string &s) { return s == contact; });
    _ui->removeListData(contact);
}

void ClientManager::sendToServer(NetworkMessage const &message) {
    lock_t lock(_locker);

    _serverConnector.getClient()->send(message);
}

std::vector<std::string> const &ClientManager::getContacts() const {
    return _contacts;
}

void ClientManager::connectSuccess() {
    _ui->displayConnectSuccess();
}

void ClientManager::authenticationSuccess() {
    _ui->displayAuthenticationSuccess();
}

void ClientManager::authenticationFailed() {
    _ui->displayAuthenticationFailed();
}

void ClientManager::authentication(){
    _ui->displayAuthentication();
    sendToServer(LoginMessage(_username));
}

void ClientManager::callContact(const std::string &contact) {
    startHost();
    sendToServer(CallRequestMessage(contact, getPort()));
    _ui->displayWaitingContactAnswer();
    _isCalling = true;
    _imHost = true;
}

void ClientManager::refuseCall(const std::tuple<std::string, std::string, unsigned short> &infosContact) {
    sendToServer(CallRefusedMessage(std::get<0>(infosContact)));
    _isCalling = false;
}

void ClientManager::callRefused() {
    _ui->displayCallRefused();
    _ui->allowCall(true);
    _isCalling = false;
}

void ClientManager::callAccepted() {
    _ui->displayCallContactAccepted();
    _ui->allowCall(false);
}

void ClientManager::acceptCall(const std::tuple<std::string, std::string, unsigned short> &infosContact) {
	if (_isCalling) {
		_ui->displayAlreadyInCall();
		sendToServer(CallRefusedMessage(std::get<0>(infosContact)));
		return;
	}
	connectToHost(std::get<1>(infosContact), std::get<2>(infosContact));
	_ui->displayCallAccepted(std::get<0>(infosContact));
	_ui->allowCall(false);
	_imHost = false;
	_isCalling = true;
}

void ClientManager::callEtablish() {
    _ui->displayCallEtablish();
	_ui->showParameter();
    new std::thread([this]() {
        std::unique_ptr<sound::Microphone>  mic(nullptr);
        std::unique_ptr<Opus>   codec(nullptr);
        std::vector<unsigned char>  bin;
        std::vector<SAMPLE> tmp;

        try {
            codec.reset(new Opus());
            mic.reset(new sound::Microphone(_volumeMicrophone));
            if (!mic)
                return;
            mic->start();
            new std::thread([this]() {
                std::unique_ptr<sound::Speaker>  speak(nullptr);
                std::unique_ptr<Opus>   codec(nullptr);
                std::vector<unsigned char>  bin;
                std::vector<SAMPLE> tmp;

                try {
                    codec.reset(new Opus());
                    speak.reset(new sound::Speaker(_volumeSpeaker));
                    speak->start();
                    while (_isCalling) {
                        _lockerSpeaker.lock();
                        while (_listSamples.begin() != _listSamples.end()) {
                            tmp = codec->decode(*_listSamples.begin());
                            _listSamples.erase(_listSamples.begin());
                            if (tmp.empty())
                                continue;
                            speak->addFrames(tmp);
                        }
                        _lockerSpeaker.unlock();
                        tmp.clear();
                        Pa_Sleep(10);
                    }
                    speak->stop();
                    //Pa_Terminate();
                }
                catch (const std::exception &error) {
                    std::cerr << error.what() << std::endl;
                }
            });
            while (_isCalling) {
                do {
                    tmp = mic->getNextSample();
                    if (tmp.size() == 0)
                        break;
                    bin = codec->encode(tmp);

                    sendToContact(VoiceDataMessage(bin));

                    bin.clear();
                } while (tmp.size() > 0);
                tmp.clear();
                Pa_Sleep(10);
            }
            mic->stop();
            //Pa_Terminate();
        }
        catch (const std::exception &error) {
            std::cerr << error.what() << std::endl;
        }
    });
}

void ClientManager::requestCall(const std::string &contact, const std::string &ip, unsigned short port) {
    _ui->displayPopupCall(std::tuple<std::string, std::string, unsigned short>(contact, ip, port));
    _ui->displayContactIsCalling(contact);
}

sizet ClientManager::getHostClients() {
    lock_t lock(_locker);

    return _server.getClients().size();
}

bool ClientManager::getImHost() const {
    return _imHost;
}

bool ClientManager::isHostClient(session_id id) {
    for (auto &keyset: _server.getClients()) {
        NetworkClient *client = keyset.second.get();

        if (client->getId() == id)
            return true;
    }
    return false;
}

bool ClientManager::getIsCalling() const {
    return _isCalling;
}

bool ClientManager::isServer(session_id id)
{
	return id == _serverConnector.getClient()->getId();
}

void ClientManager::endOfCall() {
	_ui->displayEndOfCall();
	_ui->hideParameter();
    _ui->allowCall(true);
	_isCalling = false;
}

void ClientManager::sendToContact(NetworkMessage const &message) {
    if (_imHost) {
        for (auto &client: _server.getClients())
            client.second->send(message, true);
    } else
        _hostConnector.getClient()->send(message, true);
}

void ClientManager::addSampleAudio(std::vector<unsigned char> const &samples) {
    lock_t lock(_lockerSpeaker);

    _listSamples.emplace_back(samples);
}

void ClientManager::serverDisconnect()
{
	_ui->hideAllBtn();
	_ui->displayServerDisconnected();
}
