#include "livewindow.h"
#include "mainwindow.h"
#include "ui_livewindow.h"
#include "../sound/Microphone.hpp"
#include "../sound/Speaker.hpp"
#include "../codec/Opus.hpp"
#include "../Exception.hpp"

LiveWindow::LiveWindow(QWidget *parent, const std::string &username, unsigned char *ip, unsigned short port) :
    LiveWindow(parent)
{
    this->setWindowTitle(this->windowTitle() + QString::fromStdString(username));
}

LiveWindow::LiveWindow(QWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::LiveWindow),
    _parent(parent)
{
    ui->setupUi(this);
    QIcon icon(":/resources/icon.png");
    this->setWindowIcon(icon);
    ui->connectBtn->setEnabled(true);
}

LiveWindow::~LiveWindow()
{
    delete ui;
}

void LiveWindow::on_leaveBtn_clicked()
{
    if (_parent)
        _parent->show();
    this->close();
}

void LiveWindow::on_connectBtn_clicked()
{
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

