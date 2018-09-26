#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent, const std::string &username) : SecDialog(parent)
{
    this->setWindowTitle(this->windowTitle() + QString::fromStdString(username));
}

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent, nullptr),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QIcon icon(":/resources/icon.png");
    this->setWindowIcon(icon);
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_leaveBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}
