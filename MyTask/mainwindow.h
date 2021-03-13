#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "screensfactory.h"

#include <QMainWindow>
#include <QStackedWidget>

#include <common/navigator.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget *container;
    Navigator *navigator;
    BaseScreensFactory *factory;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void navigateTo(QString tag);
    void newRootScreen(QString tag);
    void back();
    void replace(QString tag);
};
#endif // MAINWINDOW_H
