#include <iostream>
#include <regex>
#include <memory>
#include <thread>
#include <QMessageBox>
#include <QPixmap>
#include <QtCore/QCoreApplication>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "livewindow.h"
#include "../Exception.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	_child(nullptr)
{
	ui->setupUi(this);
	QPixmap pix(":/resources/logobabel.png");
	int w = ui->label_pic->width();
	int h = ui->label_pic->height();
	ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
	QIcon icon(":/resources/icon.png");
	this->setWindowIcon(icon);
    ui->lblInfos->setStyleSheet("QLabel { color : red; }");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    std::regex  r_adress("^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})$");
    std::smatch m_adress;
    std::string adress = ui->serverAdress->text().toUtf8().constData();
    unsigned char   ip[4];
    QWidget *newWindow = nullptr;

    if (std::regex_search(adress, m_adress, r_adress)){
        ip[0] = std::atoi(m_adress[1].str().c_str());
        ip[1] = std::atoi(m_adress[2].str().c_str());
        ip[2] = std::atoi(m_adress[3].str().c_str());
        ip[3] = std::atoi(m_adress[4].str().c_str());
    }
    newWindow = new LiveWindow(this
            , std::string(ui->username->text().toUtf8().constData())
            , ip
            , std::atoi(ui->serverPort->text().toUtf8().constData()));
    if (!newWindow)
        throw Exception("mainwindow: impossible to open new window");
    newWindow->show();
    this->hide();
}

void MainWindow::on_username_textChanged(const QString &arg1)
{
    std::regex r_username("^[a-zA-Z0-9-]+$");
	std::string	tmp = arg1.toUtf8().constData();

    if (!std::regex_match(tmp, r_username))
        ui->username->setText(ui->username->text().remove(ui->username->text().size() - 1, 1));
    ui->lblInfos->setText("a-Z and 0-9 allowed, 3 character minimum");
    textChanged();
}

void MainWindow::on_serverAdress_textChanged(const QString &arg1)
{
    std::regex r_adress("^[0-9.]+$");

    if (!std::regex_match(arg1.toUtf8().constData(), r_adress))
        ui->serverAdress->setText(ui->serverAdress->text().remove(ui->serverAdress->text().size() - 1, 1));
    ui->lblInfos->setText("Ip format allowed");
    textChanged();
}

void MainWindow::on_serverPort_textChanged(const QString &arg1)
{

    std::regex r_port("^[0-9]+$");

    if (!std::regex_match(arg1.toUtf8().constData(), r_port))
        ui->serverPort->setText(ui->serverPort->text().remove(ui->serverPort->text().size() - 1, 1));
    ui->lblInfos->setText("0-9, 1 character minimum and 6 maximum");
    textChanged();
}

void MainWindow::textChanged()
{
    std::regex r_username("[a-zA-Z0-9-]{3,}");
    std::regex r_adress("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    std::regex r_port("[0-9]{1,6}");

    if (std::regex_match(ui->username->text().toUtf8().constData(), r_username)
    && std::regex_match(ui->serverAdress->text().toUtf8().constData(), r_adress)
    &&  std::regex_match(ui->serverPort->text().toUtf8().constData(), r_port)) {
        ui->lblInfos->setText("");
        ui->lblInfos->setStyleSheet("QLabel { color : green; }");
        if (!ui->pushButton_Login->isEnabled())
            ui->pushButton_Login->setEnabled(true);
    } else {
        if (ui->pushButton_Login->isEnabled())
            ui->pushButton_Login->setEnabled(false);
        ui->lblInfos->setStyleSheet("QLabel { color : red; }");
    }
}
