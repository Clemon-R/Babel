#include "livewindow.h"
#include "mainwindow.h"
#include "soundmanagerwindow.h"
#include "receptioncallwindow.h"
#include "ui_livewindow.h"
#include "../sound/Microphone.hpp"
#include "../sound/Speaker.hpp"
#include "../codec/Opus.hpp"
#include "../Exception.hpp"
#include <thread>
#include "client/src/network/ClientController.h"

LiveWindow::LiveWindow(QWidget *parent, const std::string &username, const std::string &ip, unsigned short port) :
    LiveWindow(parent)
{
	this->_username = username;
    this->setWindowTitle(this->windowTitle().append(QString::fromStdString(username)));
    _manager.reset(new ClientManager(this, username));
    if (!_manager)
        throw Exception("livewindow: error while allocating memory");
    _manager->connect(ip, port);
}

LiveWindow::LiveWindow(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::LiveWindow),
    _parent(parent),
    _child(nullptr),
    _call(nullptr),
    _volumeSpeaker(100),
    _volumeMicrophone(100),
    _state(false)
{
    ui->setupUi(this);
    QIcon icon(":/resources/icon.png");
    this->setWindowIcon(icon);
}

LiveWindow::~LiveWindow()
{
    delete ui;
}

void LiveWindow::on_leaveBtn_clicked()
{
    if (_parent)
        _parent->show();
    _state = false;
    this->close();
}

void	LiveWindow::setState(bool state)
{
	_state = state;
	ui->closeBtn->setEnabled(state);
	ui->connectBtn->setEnabled(!state);
	if (state) {
		new std::thread([this]() {
			std::unique_ptr<sound::Microphone>  mic(nullptr);
			std::unique_ptr<sound::Speaker>  speak(nullptr);
			std::unique_ptr<Opus>   codec(nullptr);
			std::tuple<unsigned char *, int>    bin;
			std::vector<SAMPLE> tmp;

			try {
				codec.reset(new Opus());
				speak.reset(new sound::Speaker(_volumeSpeaker));
				mic.reset(new sound::Microphone(_volumeMicrophone));
				if (!mic)
					return;
				mic->start();
				speak->start();
				while (_state) {
					do {
						if (tmp.size() > 0)
							speak->addFrames(tmp);
						tmp = mic->getNextSample();
						if (tmp.size() == 0)
							break;
						bin = codec->encode(tmp);
						tmp = codec->decode(bin);
						if (std::get<0>(bin))
							delete[] std::get<0>(bin);
					} while (tmp.size() > 0);
					tmp.clear();
					Pa_Sleep(10);
				}
				mic->stop();
				speak->stop();
				Pa_Terminate();
			}
			catch (const std::exception &error) {
				std::cerr << error.what() << std::endl;
			}
		});
	}
}

void LiveWindow::on_connectBtn_clicked()
{
	_call = new ReceptionCallWindow(this, std::bind(&LiveWindow::setState, this, std::placeholders::_1), this->_username);
	_call->show();    
}


void LiveWindow::on_parameterBtn_clicked()
{
    _child = new SoundManagerWindow(this, _volumeSpeaker, _volumeMicrophone);
    if (!_child)
        throw Exception("livewindow: impossible to create new window");
    _child->show();
}

void LiveWindow::displayConnectSuccess() {
	QMetaObject::invokeMethod(ui->infos, "setText", Qt::DirectConnection, Q_ARG(QString, "Connected to the server"));
	QMetaObject::invokeMethod(ui->infos, "setStyleSheet", Qt::DirectConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayAuthenticationSuccess() {
	QMetaObject::invokeMethod(ui->infos, "setText", Qt::DirectConnection, Q_ARG(QString, "Authentication successfull"));
	QMetaObject::invokeMethod(ui->infos, "setStyleSheet", Qt::DirectConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayAuthenticationFailed() {
	QMetaObject::invokeMethod(ui->infos, "setText", Qt::DirectConnection, Q_ARG(QString, "Authentication failed"));
	QMetaObject::invokeMethod(ui->infos, "setStyleSheet", Qt::DirectConnection, Q_ARG(QString, "QLabel { color : red; }"));
}

void LiveWindow::displayAuthentication() {
	QMetaObject::invokeMethod(ui->infos, "setText", Qt::DirectConnection, Q_ARG(QString, "Authentication in progress..."));
	QMetaObject::invokeMethod(ui->infos, "setStyleSheet", Qt::DirectConnection, Q_ARG(QString, "QLabel { color : black; }"));
}

void LiveWindow::insertListData(const std::string &name) {
    QMetaObject::invokeMethod(ui->contactList, "addItem", Qt::DirectConnection, Q_ARG(QString, QString::fromStdString(name)));
}

void LiveWindow::on_contactList_clicked(const QModelIndex &index)
{
	(void)index;
	if (!ui->contactList->selectedItems().isEmpty())
		std::cout << ui->contactList->selectedItems().at(0)->text().toStdString() << std::endl;
}

void LiveWindow::on_contactList_doubleClicked(const QModelIndex &index)
{
	on_contactList_clicked(index);
}

void LiveWindow::on_closeBtn_clicked()
{
    ui->closeBtn->setEnabled(false);
    ui->connectBtn->setEnabled(true);
    _state = false;
}
