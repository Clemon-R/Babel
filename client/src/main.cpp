//
// Created by raphael on 22/09/18.
//
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include "ui_mainwindow.h"
#include "forms/mainwindow.h"
#ifdef _WIN32
#include <Windows.h>
#endif

int main(int argc, char *argv[])
{
#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), 0);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}