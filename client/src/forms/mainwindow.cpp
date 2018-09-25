#include <iostream>
#include <regex>
#include <memory>
#include <thread>
#include <QMessageBox>
#include <QPixmap>
#include <QtCore/QCoreApplication>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "secdialog.h"
#include "../sound/Microphone.hpp"
#include "../sound/Speaker.hpp"
#include "../codec/Opus.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QPixmap pix(":/resources/logobabel.png");
	int w = ui->label_pic->width();
	int h = ui->label_pic->height();
	ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->lblInfos->setStyleSheet("QLabel { color : red; }");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
	QString username = ui->username->text();
    QString ip = ui->serverAdress->text();
    QString port = ui->serverPort->text();
	secDialog = new SecDialog();
	this->hide();
	secDialog->show();
	return;
    std::unique_ptr<sound::Microphone>  mic(nullptr);
    std::unique_ptr<sound::Speaker>  speak(nullptr);
    std::unique_ptr<Opus>   codec(nullptr);
    std::tuple<unsigned char *, int>    bin;
    std::vector<SAMPLE> tmp;

    try{
        codec.reset(new Opus());
        speak.reset(new sound::Speaker());
        mic.reset(new sound::Microphone());
        if (!mic)
            return;
        mic->start();
        speak->start();
        for (int i = 0;i < 100;i++){
            do {
                speak->addFrames(tmp);
                bin = codec->encode(mic->getNextSample());
                tmp = codec->decode(bin);
                if (std::get<0>(bin))
                    delete [] std::get<0>(bin);
            }while (tmp.size() > 0);
            Pa_Sleep(100);
        }
        mic->stop();
        speak->stop();
        Pa_Terminate();
    }catch (const std::exception &error){
        std::cerr << error.what() << std::endl;
    }
}

void MainWindow::on_username_textChanged(const QString &arg1)
{
    (void)arg1;
    textChanged();
}

void MainWindow::on_serverAdress_textChanged(const QString &arg1)
{
    (void)arg1;
    textChanged();
}

void MainWindow::on_serverPort_textChanged(const QString &arg1)
{
    (void)arg1;
    textChanged();
}

void MainWindow::textChanged()
{
    std::regex r_username("[a-zA-Z0-9-]{3,}");
    std::regex r_adress("[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}");
    std::regex r_port("[0-9]{1,6}");

    if (std::regex_match(ui->username->text().toLocal8Bit().toStdString(), r_username)
    && std::regex_match(ui->serverAdress->text().toLocal8Bit().toStdString(), r_adress)
    &&  std::regex_match(ui->serverPort->text().toLocal8Bit().toStdString(), r_port)) {
        ui->lblInfos->setText("ok");
        ui->lblInfos->setStyleSheet("QLabel { color : green; }");
        ui->pushButton_Login->setEnabled(true);
    }
}
