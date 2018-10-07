//
// Created by romain on 06/10/18.
//

#ifndef BABEL_CLIENTMANAGER_H
#define BABEL_CLIENTMANAGER_H


#include <shared/hook/HookNetworkConnector.h>
#include <shared/hook/HookNetworkServer.h>
#include <memory>
#include <tuple>
class LiveWindow;
class ClientController;

class ClientManager {
public:
    ClientManager(LiveWindow *, const std::string &, int &volumeSpeaker, int &volumeMicrophone);

    void    startHost();
    void    closeAllClients();
    void    closeConnection();
	void	close();
    boost::uint16_t getPort();
    void    connectToServer(std::string const &host, uint16_t port);
    void    connectToHost(std::string const &host, uint16_t port);
    void    addContact(std::string const &contact);
    void    delContact(std::string const &contact);
    void    callContact(const std::string &contact);
    void    requestCall(const std::string &contact, const std::string &ip, unsigned short port);
    void    refuseCall(const std::tuple<std::string, std::string, unsigned short>);
    void    acceptCall(const std::tuple<std::string, std::string, unsigned short>);
    void    callRefused();
    void    callAccepted();
    void    callEtablish();
    void    endOfCall();
    void    sendToServer(NetworkMessage const &message);
    void    sendToContact(NetworkMessage const &message);
    void    addSampleAudio(std::vector<unsigned char> const &samples);
	void	serverDisconnect();

    std::vector<std::string> const &getContacts() const;
    bool    getImHost() const;
    bool    getIsCalling() const;
	bool	isServer(session_id id);

    void    connectSuccess();
    void    authentication();
    void    authenticationSuccess();
    void    authenticationFailed();
    sizet   getHostClients();
    bool    isHostClient(session_id id);
private:
    std::unique_ptr<ClientController> _controller;
    HookNetworkConnector _serverConnector;
    HookNetworkConnector _hostConnector;
    HookNetworkServer _server;
    std::mutex _locker;
    std::mutex _lockerSpeaker;
    LiveWindow *_ui;

    std::string _username;
    std::vector<std::string> _contacts;
    bool _imHost;
    bool _isCalling;
    int &_volumeSpeaker;
    int &_volumeMicrophone;
    std::vector<std::vector<unsigned char>> _listSamples;
};


#endif //BABEL_CLIENTMANAGER_H
