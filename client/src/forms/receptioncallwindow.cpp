#include "receptioncallwindow.h"
#include "ui_receptioncallwindow.h"

ReceptionCallWindow::ReceptionCallWindow(QWidget *parent, ClientManager *manager) :
	QDialog(parent),
	ui(new Ui::ReceptionCallWindow),
	_manager(manager)
{
	ui->setupUi(this);

	this->setWindowTitle(QString::fromStdString(_manager->getCallContact()).append(this->windowTitle()));
}

ReceptionCallWindow::~ReceptionCallWindow()
{
    delete ui;
}

void ReceptionCallWindow::on_buttonBox_rejected()
{
	_manager->refuseCall();
}

void ReceptionCallWindow::on_accept_clicked()
{
	_manager->acceptCall();
	this->close();
}
