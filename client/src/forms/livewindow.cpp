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
	ui->btnParameter->hide();
	this->_username = username;
    this->setWindowTitle(this->windowTitle().append(QString::fromStdString(username)));
    _manager.reset(new ClientManager(this, username, _volumeSpeaker, _volumeMicrophone));
	_manager->connectToServer(ip, port);
}

LiveWindow::LiveWindow(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::LiveWindow),
    _parent(parent),
    _child(nullptr),
    _call(nullptr),
    _volumeSpeaker(100),
    _volumeMicrophone(100)
{
    ui->setupUi(this);
    QIcon icon(":/resources/icon.png");
    this->setWindowIcon(icon);
}

LiveWindow::~LiveWindow()
{
    delete ui;
}

void LiveWindow::on_btnLeave_clicked()
{
    if (_parent) {
		//_parent->move(geometry().center() - _parent->geometry().center());
		_parent->show();
	}
	on_btnClose_clicked();
	_manager->close();
    this->close();
}

void	LiveWindow::setState(bool state)
{
	/*_state = state;
	ui->btnClose->setEnabled(state);
	ui->btnCall->setEnabled(!state);
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
	}*/
}

void LiveWindow::on_btnCall_clicked()
{
	if (_manager->getIsCalling() || ui->listContact->selectedItems().isEmpty())
		return;
	_contactCalled = ui->listContact->selectedItems().at(0)->text().toUtf8().toStdString();
	_manager->callContact(_contactCalled);
}


void LiveWindow::on_btnParameter_clicked()
{
    _child = new SoundManagerWindow(this, _volumeSpeaker, _volumeMicrophone);
	_child->move(geometry().center() - _child->geometry().center());
    _child->show();
}

void LiveWindow::on_btnClose_clicked()
{
	if (!_manager->getIsCalling())
		return;
	_manager->closeCall();
}

void LiveWindow::displayConnectSuccess() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Connected to the server"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayAuthenticationSuccess() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Authentication successfull"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayAuthenticationFailed() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Authentication failed"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : red; }"));
}

void LiveWindow::displayAuthentication() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Authentication in progress..."));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : black; }"));
}

void LiveWindow::displayWaitingContactAnswer() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Waiting " + QString::fromStdString(_contactCalled) + " to reply..."));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : black; }"));
}

void LiveWindow::displayContactIsCalling(const std::string &name) {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(name) + " is calling..."));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : black; }"));
}

void LiveWindow::displayCallRefused()  {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Call from " + QString::fromStdString(_contactCalled) + " refused"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : red; }"));
}

void LiveWindow::displayCallAccepted(const std::string &name) {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Call from " + QString::fromStdString(name) + " accepted"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayCallContactAccepted() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(_contactCalled) + " accepted the call"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayEndOfCall() {
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "End of the call"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : black; }"));
}

void LiveWindow::displayCallEtablish() {
    QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Call etablish"));
    QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : green; }"));
}

void LiveWindow::displayServerDisconnected()
{
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "Server disconnected"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : red; }"));
}

void LiveWindow::displayAlreadyInCall()
{
	QMetaObject::invokeMethod(ui->lblInfos, "setText", Qt::QueuedConnection, Q_ARG(QString, "You are already in call"));
	QMetaObject::invokeMethod(ui->lblInfos, "setStyleSheet", Qt::QueuedConnection, Q_ARG(QString, "QLabel { color : red; }"));
}

void LiveWindow::insertListData(const std::string &name) {
    QMetaObject::invokeMethod(this, "addItemList", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(name)));
}

void LiveWindow::removeListData(const std::string &name) {
	QMetaObject::invokeMethod(this, "removeItemList", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(name)));
}

void LiveWindow::hideAllBtn()
{
	QMetaObject::invokeMethod(ui->btnCall, "hide", Qt::QueuedConnection);
	QMetaObject::invokeMethod(ui->btnClose, "hide", Qt::QueuedConnection);
	QMetaObject::invokeMethod(ui->btnParameter, "hide", Qt::QueuedConnection);
}

void LiveWindow::showParameter()
{
	QMetaObject::invokeMethod(ui->btnParameter, "show", Qt::QueuedConnection);
}

void LiveWindow::hideParameter()
{
	QMetaObject::invokeMethod(ui->btnParameter, "hide", Qt::QueuedConnection);
}

void LiveWindow::displayPopupCall(const std::tuple<std::string, std::string, unsigned short> &infosContact) {
	QMetaObject::invokeMethod(this, "openPopupCall", Qt::QueuedConnection, Q_ARG(QString, QString::fromStdString(std::get<0>(infosContact))), Q_ARG(QString, QString::fromStdString(std::get<1>(infosContact))), Q_ARG(unsigned short, std::get<2>(infosContact)));
}

void LiveWindow::openPopupCall(const QString &name, const QString &ip, const unsigned short port) {
	_call = new ReceptionCallWindow(this, _manager.get(), std::tuple<std::string, std::string, unsigned short>(name.toUtf8().toStdString(), ip.toUtf8().toStdString(), port));
	if (!_call)
		throw Exception("livewindow: impossible to create new window");
	_call->move(geometry().center() - _call->geometry().center());
	_call->show();
}

void LiveWindow::addItemList(const QString &name) {
	ui->listContact->addItem(name);
}

void LiveWindow::removeItemList(const QString &name) {
	QList<QListWidgetItem *>	list = ui->listContact->findItems(name, Qt::MatchFlag::MatchExactly);
	int row;

	for (auto &item : list){
		row = ui->listContact->row(item);
		ui->listContact->takeItem(row);
	}
}

void LiveWindow::on_listContact_clicked(const QModelIndex &index)
{
	(void)index;
	ui->btnCall->setEnabled(!_manager->getIsCalling() && !ui->listContact->selectedItems().isEmpty());
}

void LiveWindow::on_listContact_doubleClicked(const QModelIndex &index)
{
	on_listContact_clicked(index);
	on_btnCall_clicked();
}

void LiveWindow::allowCall(bool state) {
	ui->btnCall->setEnabled(state && !ui->listContact->selectedItems().isEmpty());
	ui->btnClose->setEnabled(!state);
}
