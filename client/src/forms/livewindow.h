#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QWidget>
#include <memory>
#include <client/src/ClientManager.h>

namespace Ui {
class LiveWindow;
}

class LiveWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LiveWindow(QWidget *parent = 0);
    LiveWindow(QWidget *parent, const std::string &username, const std::string &ip, unsigned short port);
    ~LiveWindow();

    void    insertListData(const std::string &name);

    void    displayConnectSuccess();
    void    displayAuthentication();
    void    displayAuthenticationSuccess();
    void    displayAuthenticationFailed();
private slots:
    void    on_contactList_doubleClicked(const QModelIndex &index);
    void    on_contactList_clicked(const QModelIndex &index);
    void    addItemList(const QString &name);

private slots:
    void on_closeBtn_clicked();
    void on_parameterBtn_clicked();
    void on_connectBtn_clicked();
    void on_leaveBtn_clicked();

private:
	void	setState(bool);

    Ui::LiveWindow *ui;
    QWidget *_parent;
    QDialog *_child;
	QDialog	*_call;

    int _volumeSpeaker;
    int _volumeMicrophone;
    bool _state;
	std::string	_username;

	std::unique_ptr<ClientManager>	_manager;
};

#endif // LIVEWINDOW_H
