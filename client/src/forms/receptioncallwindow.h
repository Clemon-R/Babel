#ifndef RECEPTIONCALLWINDOW_H
#define RECEPTIONCALLWINDOW_H

#include <QDialog>
#include <functional>
#include <client/src/ClientManager.h>

namespace Ui {
class ReceptionCallWindow;
}

class ReceptionCallWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReceptionCallWindow(QWidget *parent, ClientManager *manager);
    ~ReceptionCallWindow();

private slots:
    void on_buttonBox_rejected();

    void on_accept_clicked();

private:
    Ui::ReceptionCallWindow *ui;
    ClientManager	*_manager;
};

#endif // RECEPTIONCALLWINDOW_H
