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

    void 	allowCall(bool);

    void    insertListData(const std::string &name);
    void    removeListData(const std::string &name);

    void    displayConnectSuccess();
    void    displayAuthentication();
    void    displayAuthenticationSuccess();
    void    displayAuthenticationFailed();
    void	displayWaitingContactAnswer();
    void	displayContactIsCalling();
    void	displayCallRefused();
    void	displayCallAccepted();
    void	displayCallContactAccepted();
    void 	displayPopupCall();
    void	displayEndOfCall();
    void 	displayCallEtablish();
private slots:
    void    on_listContact_doubleClicked(const QModelIndex &index);
    void    on_listContact_clicked(const QModelIndex &index);
    void    addItemList(const QString &name);
    void    removeItemList(const QString &name);

    void	openPopupCall();
private slots:
    void on_btnClose_clicked();
    void on_btnParameter_clicked();
    void on_btnCall_clicked();
    void on_btnLeave_clicked();

private:
	void	setState(bool);

    Ui::LiveWindow *ui;
    QWidget *_parent;
    QDialog *_child;
	QDialog	*_call;

    int _volumeSpeaker;
    int _volumeMicrophone;
	std::string	_username;
	std::string	_contactCalled;

	std::unique_ptr<ClientManager>	_manager;
};

#endif // LIVEWINDOW_H
