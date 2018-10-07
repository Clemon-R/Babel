#include "receptioncallwindow.h"
#include "ui_receptioncallwindow.h"

ReceptionCallWindow::ReceptionCallWindow(QWidget *parent, ClientManager *manager, const std::tuple<std::string, std::string, unsigned short> infosContact) :
	QDialog(parent),
	ui(new Ui::ReceptionCallWindow),
	_manager(manager),
	_infosContact(infosContact)
{
	ui->setupUi(this);

	this->setWindowTitle(QString::fromStdString(std::get<0>(_infosContact)).append(this->windowTitle()));
}

ReceptionCallWindow::~ReceptionCallWindow()
{
    delete ui;
}

void ReceptionCallWindow::on_buttonBox_rejected()
{
	_manager->refuseCall(_infosContact);
}

void ReceptionCallWindow::on_accept_clicked()
{
	_manager->acceptCall(_infosContact);
	this->close();
}
