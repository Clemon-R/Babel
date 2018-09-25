//
// Created by raphael on 22/09/18.
//
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include "ui_mainwindow.h"
#include "forms/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}