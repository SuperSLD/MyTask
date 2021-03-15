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
};
#endif // MAINWINDOW_H
