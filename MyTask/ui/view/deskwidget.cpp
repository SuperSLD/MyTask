#include "deskwidget.h"

#include <models/deskmodel.h>

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

#include <style/stylecontainer.h>
using namespace styles;

DeskWidget::DeskWidget(DeskModel desk) {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *title = new QLabel(desk.title);
    QFrame *descriptionConteiner = new QFrame;
    QVBoxLayout *descriptionLayout = new QVBoxLayout;
    QLabel *description = new QLabel(desk.description);

    QHBoxLayout *bottomContainer = new QHBoxLayout;
    QLabel *users = new QLabel(QString::number(desk.users.length()) + " участников");
    QLabel *progress= new QLabel(desk.getProgress() + " пунктов выполнено");


    title->setStyleSheet(TEXT_DARK_LABLE);
    title->setContentsMargins(24,24,24,24);
    title->setWordWrap(true);
    title->setMaximumWidth(325);

    description->setMaximumWidth(325);
    description->setWordWrap(true);
    description->setStyleSheet(TEXT_HINT_LABLE);
    descriptionLayout->addWidget(description);
    descriptionConteiner->setLayout(descriptionLayout);
    descriptionConteiner->setStyleSheet("background-color:"+COLOR_BORDER+";");
    descriptionLayout->setContentsMargins(24,24,24,24);

    users->setStyleSheet(TEXT_DARK_SMAL_LABLE);
    progress->setStyleSheet(TEXT_PRIMARY_SMAL_LABLE);
    bottomContainer->addWidget(users);
    bottomContainer->addWidget(progress);
    bottomContainer->setContentsMargins(24,8,24,16);

    this->setMinimumHeight(100);

    mainLayout->setContentsMargins(0,0,0,0);

    mainLayout->addWidget(title);
    mainLayout->addWidget(descriptionConteiner);
    mainLayout->addLayout(bottomContainer);
    this->setLayout(mainLayout);
    this->setMaximumWidth(396);
    this->setMinimumWidth(396);
    this->setObjectName("desk");
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setStyleSheet(DESK_WIDGET);
}
