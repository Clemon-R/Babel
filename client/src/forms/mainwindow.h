#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secdialog.h"
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	    Q_OBJECT

public:
	    explicit MainWindow(QWidget *parent = 0);
	    ~MainWindow();

	    private slots:
		    void on_pushButton_Login_clicked();
            void on_username_textChanged(const QString &);
            void on_serverAdress_textChanged(const QString &);
            void on_serverPort_textChanged(const QString &);

private:
            void textChanged();
		    Ui::MainWindow *ui;
		    SecDialog *secDialog;
};

#endif // MAINWINDOW_H
