#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <iostream>

#include <memory>
#include <thread>
#include <QtCore/QCoreApplication>
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

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
	QString username = ui->LineEditUsername->text();
	QString host = ui->LineEditAdress->text();
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
