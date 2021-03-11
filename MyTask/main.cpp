#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //Поддержка HighDpi в проекте.
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
