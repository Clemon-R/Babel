#include "receptioncallwindow.h"
#include "ui_receptioncallwindow.h"

ReceptionCallWindow::ReceptionCallWindow(QWidget *parent, std::function<void(bool)> func, const std::string &username) :
	QDialog(parent),
	ui(new Ui::ReceptionCallWindow),
	_state(func)
{
	ui->setupUi(this);

	this->setWindowTitle(QString::fromStdString(username).append(this->windowTitle()));
}

ReceptionCallWindow::~ReceptionCallWindow()
{
    delete ui;
}

void ReceptionCallWindow::on_buttonBox_rejected()
{
	_state(false);
}

void ReceptionCallWindow::on_accept_clicked()
{
	_state(true);
	this->close();
}
