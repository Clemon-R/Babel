#ifndef RECEPTIONCALLWINDOW_H
#define RECEPTIONCALLWINDOW_H

#include <QDialog>

namespace Ui {
class ReceptionCallWindow;
}

class ReceptionCallWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReceptionCallWindow(QWidget *parent = nullptr);
    ~ReceptionCallWindow();

private:
    Ui::ReceptionCallWindow *ui;
};

#endif // RECEPTIONCALLWINDOW_H
