#include "receptioncallwindow.h"
#include "ui_receptioncallwindow.h"

ReceptionCallWindow::ReceptionCallWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceptionCallWindow)
{
    ui->setupUi(this);
}

ReceptionCallWindow::~ReceptionCallWindow()
{
    delete ui;
}
