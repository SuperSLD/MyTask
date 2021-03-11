#include "mainwindow.h"
#include "screensfactory.h"
#include <common/navigator.h>

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   

    container = new QStackedWidget;
    container->setObjectName("ui");

    this->factory = new ScreensFactory;
    this->navigator = new Navigator(
                this->container,
                this->factory
    );

    QString mainStyle = "QWidget {"
                        "background-color:#EFF5FC;"
                        "}";
    container->setStyleSheet(mainStyle);

    this->setWindowTitle("MyTask");
    this->setWindowIcon(QIcon(":/resc/resc/icon.svg"));
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    this->setCentralWidget(container);
}

MainWindow::~MainWindow() {
    delete container;
    delete navigator;
    delete factory;
}

