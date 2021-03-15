#include "splashfragment.h"

#include <QFrame>
#include <QLabel>
#include <QSettings>
#include <QTimer>
#include <QVBoxLayout>
#include <qsvgwidget.h>

#include <style/stylecontainer.h>
#include <screensfactory.h>
using namespace styles;
using namespace screens;

SplashFragment::SplashFragment() {
    qDebug("SplashFragment crete");

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QSvgWidget *centerConainer = new QSvgWidget(":/resc/resc/splash.svg");

    centerConainer->setStyleSheet(SPLASH_ICON);

    mainHLayout->addWidget(centerConainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");
    this->setLayout(mainVLayout);

    QTimer::singleShot(3000, this, SLOT(openStartScreen()));
    qDebug("SplashFragment crete finished!!");
}

SplashFragment::~SplashFragment() {

}

void SplashFragment::openStartScreen() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    if(settings->value("token", "").toString() != "") {
        newRootScreen(MAIN_TAG);
    } else {
        newRootScreen(START_TAG);
    }
}
