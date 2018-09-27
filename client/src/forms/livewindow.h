#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QWidget>

namespace Ui {
class LiveWindow;
}

class LiveWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LiveWindow(QWidget *parent = 0);
    LiveWindow(QWidget *parent, const std::string &username, unsigned char *ip, unsigned short port);
    ~LiveWindow();

private slots:
    void on_connectBtn_clicked();
    void on_leaveBtn_clicked();

private:
    Ui::LiveWindow *ui;
    QWidget *_parent;
};

#endif // LIVEWINDOW_H
