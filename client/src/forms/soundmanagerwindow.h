#ifndef SOUNDMANAGERWINDOW_H
#define SOUNDMANAGERWINDOW_H

#include <QDialog>

namespace Ui {
class SoundManagerWindow;
}

class SoundManagerWindow : public QDialog
{
    Q_OBJECT

public:
    SoundManagerWindow(QWidget *parent, int &speaker, int &microphone);
    ~SoundManagerWindow();

private slots:
    void on_speakerSlider_sliderMoved(int position);
    void on_microphoneSlider_sliderMoved(int position);
    void on_saveBtn_rejected();

private:
    Ui::SoundManagerWindow *ui;

    int &_volumeSpeaker;
    int &_volumeMicrophone;
    int _oldSpeaker;
    int _oldMicrophone;
};

#endif // SOUNDMANAGERWINDOW_H
