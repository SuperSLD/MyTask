#include "startfragment.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>
#include <QVBoxLayout>
#include "style/stylecontainer.h"
#include "screensfactory.h"

using namespace styles;
using namespace screens;

StartFragment::StartFragment(){
    qDebug("SplashFragnebt crete");

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerConainer = new QFrame;

    QVBoxLayout *startMainLayout = new QVBoxLayout;
    QHBoxLayout *startContent = new QHBoxLayout;
    QSvgWidget *mainImage = new QSvgWidget(":/resc/resc/finances.svg");

    QVBoxLayout *startVerticalContent = new QVBoxLayout;
    QLabel *title = new QLabel("Добрый день");
    QLabel *subtitle = new QLabel("Вы вошли в приложение которое поможет составить вам рабочий план и придердиваться его для достижения своих целей.");

    QVBoxLayout *buttonContainer = new QVBoxLayout;

    QPushButton *loginButton = new QPushButton("Войти");
    QPushButton *regButton = new QPushButton("Зарегестрироваться");

    title->setStyleSheet(TITLE_LABLE);
    subtitle->setStyleSheet(HINT_LABLE);
    subtitle->setMaximumWidth(335);
    subtitle->setMinimumWidth(335);
    subtitle->setWordWrap(true);
    startVerticalContent->addWidget(title);
    startVerticalContent->addWidget(subtitle);
    startVerticalContent->setAlignment(Qt::AlignTop);
    buttonContainer->setAlignment(Qt::AlignBottom);

    startMainLayout->addLayout(startVerticalContent);
    startMainLayout->addLayout(buttonContainer);

    loginButton->setStyleSheet(BUTTON_SOLID);
    connect(loginButton, &QPushButton::clicked, this, &StartFragment::openLogin);
    regButton->setStyleSheet(BUTTON_EMPTY);
    connect(regButton, &QPushButton::clicked, this, &StartFragment::openRegistration);
    buttonContainer->addWidget(loginButton);
    buttonContainer->addWidget(regButton);

    startContent->setContentsMargins(46,46,46,46);
    mainImage->setContentsMargins(24,0,56,0);

    centerConainer->setStyleSheet(FRAME_8PX_WHITE);
    centerConainer->setLayout(startContent);
    mainImage->setStyleSheet(START_ICON);
    startContent->addWidget(mainImage);
    startContent->addLayout(startMainLayout);

    mainHLayout->addWidget(centerConainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainVLayout);
}

StartFragment::~StartFragment() {

}

void StartFragment::openLogin() {
    navigateTo(LOGIN_TAG);
}

void StartFragment::openRegistration() {
    navigateTo(REGISTRATION_TAG);
}
