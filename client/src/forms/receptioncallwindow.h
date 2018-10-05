#ifndef RECEPTIONCALLWINDOW_H
#define RECEPTIONCALLWINDOW_H

#include <QDialog>
#include <functional> 

namespace Ui {
class ReceptionCallWindow;
}

class ReceptionCallWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReceptionCallWindow(QWidget *parent, std::function<void (bool)> func, const std::string &);
    ~ReceptionCallWindow();

private slots:
    void on_buttonBox_rejected();

    void on_accept_clicked();

private:
    Ui::ReceptionCallWindow *ui;
	std::function<void(bool)>	_state;
};

#endif // RECEPTIONCALLWINDOW_H
