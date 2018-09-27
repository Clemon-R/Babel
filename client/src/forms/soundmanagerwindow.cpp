#include "soundmanagerwindow.h"
#include "ui_soundmanagerwindow.h"

SoundManagerWindow::SoundManagerWindow(QWidget *parent, int &speaker, int &microphone) :
    QDialog(parent),
    ui(new Ui::SoundManagerWindow),
    _volumeSpeaker(speaker),
    _volumeMicrophone(microphone),
    _oldSpeaker(speaker),
    _oldMicrophone(microphone)
{
    ui->setupUi(this);
    ui->speakerSlider->setValue(_volumeSpeaker);
    ui->microphoneSlider->setValue(_volumeMicrophone);
    ui->displaySpeaker->display(_volumeSpeaker);
    ui->displayMicrophone->display(_volumeMicrophone);
}

SoundManagerWindow::~SoundManagerWindow()
{
    delete ui;
}

void SoundManagerWindow::on_saveBtn_rejected()
{
    _volumeSpeaker = _oldSpeaker;
    _volumeMicrophone = _oldMicrophone;
}

void SoundManagerWindow::on_microphoneSlider_sliderMoved(int position)
{
    ui->displayMicrophone->display(position);
    _volumeMicrophone = ui->microphoneSlider->value();
}

void SoundManagerWindow::on_speakerSlider_sliderMoved(int position)
{
    ui->displaySpeaker->display(position);
    _volumeSpeaker = ui->speakerSlider->value();
}
