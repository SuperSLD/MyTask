#include "mainfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>
#include <QVBoxLayout>
using namespace screens;

MainFragment::MainFragment() {
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *profileContainer = new QVBoxLayout;

    QPushButton *inviteButton = new QPushButton("Мои приглашения");
    QPushButton *addButton = new QPushButton("Создать доску");
    QPushButton *exitButton = new QPushButton("Выйти из профиля");

    QVBoxLayout *userContainer = new QVBoxLayout;
    QSvgWidget *profileImage = new QSvgWidget(":/resc/resc/user_circle.svg");
    QLabel *userName = new QLabel("@user");

    profileImage->setMaximumSize(QSize(100,100));
    profileImage->setContentsMargins(35,35,35,24);
    profileImage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    userContainer->addWidget(profileImage);
    userName->setStyleSheet(TITLE_LABLE);
    userName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    userName->setContentsMargins(35,0,35,24);
    userContainer->addWidget(userName);
    userContainer->setAlignment(Qt::AlignCenter);

    inviteButton->setStyleSheet(BUTTON_PROFILE);
    inviteButton->setMaximumWidth(270);
    addButton->setStyleSheet(BUTTON_PROFILE);
    addButton->setMaximumWidth(270);
    exitButton->setStyleSheet(BUTTON_PROFILE_RED);
    exitButton->setMaximumWidth(270);
    profileContainer->addLayout(userContainer);
    profileContainer->addWidget(inviteButton);
    profileContainer->addWidget(addButton);
    profileContainer->addWidget(exitButton);
    profileContainer->setAlignment(Qt::AlignTop);

    mainHLayout->addLayout(profileContainer);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
}

MainFragment::~MainFragment() {
    delete networkManager;
}
