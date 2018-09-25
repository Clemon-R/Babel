#include "secdialog.h"
#include "ui_secdialog.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent, nullptr),
    ui(new Ui::SecDialog)
{
   // ui->setupUi(this);
}

SecDialog::~SecDialog()
{
    delete ui;
}
