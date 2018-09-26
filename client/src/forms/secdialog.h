#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <iostream>
#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    SecDialog(QWidget *parent, const std::string &);
    ~SecDialog();

private slots:
    void on_leaveBtn_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
