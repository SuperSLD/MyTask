#include "invitewidget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <style/stylecontainer.h>
using namespace styles;


InviteWidget::InviteWidget(DeskModel *desk, QString id) {
    this->model = desk;
    this->id = id;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *title = new QLabel(desk->title);
    QFrame *descriptionConteiner = new QFrame;
    QVBoxLayout *descriptionLayout = new QVBoxLayout;
    QLabel *description = new QLabel(desk->description);

    QHBoxLayout *bottomContainer = new QHBoxLayout;
    QLabel *users = new QLabel(QString::number(desk->users.length()) + " участников");
    QLabel *progress= new QLabel(desk->getProgress() + " пунктов выполнено");

    QHBoxLayout *buttonContainer = new QHBoxLayout;
    QPushButton *acceptButton = new QPushButton("Принять");
    QPushButton *cancelButton = new QPushButton("Отклонить");


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

    users->setStyleSheet(TEXT_PRIMARY_SMAL_LABLE);
    progress->setStyleSheet(TEXT_HINT_SMAL_LABLE);
    bottomContainer->addWidget(users);
    bottomContainer->addWidget(progress);
    bottomContainer->setContentsMargins(24,8,24,8);

    cancelButton->setStyleSheet(BUTTON_SOLID);
    //openButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    cancelButton->setContentsMargins(24,0,24,24);
    connect(cancelButton, &QPushButton::clicked, this, &InviteWidget::buttonCancel);
    buttonContainer->addWidget(cancelButton);
    acceptButton->setStyleSheet(BUTTON_EMPTY);
    //openButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    buttonContainer->setContentsMargins(24,0,24,24);
    connect(acceptButton, &QPushButton::clicked, this, &InviteWidget::buttonAccept);
    buttonContainer->addWidget(acceptButton);
    //buttonContainer->setAlignment(Qt::AlignRight);

    //this->setMinimumHeight(100);

    mainLayout->setContentsMargins(0,0,0,0);


    mainLayout->addWidget(title);
    mainLayout->addWidget(descriptionConteiner);
    mainLayout->addLayout(bottomContainer);
    mainLayout->addLayout(buttonContainer);
    this->setLayout(mainLayout);
    this->setMaximumWidth(396);
    this->setMinimumWidth(396);
    this->setObjectName("desk");
    this->setMinimumHeight(mainLayout->geometry().height());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->setStyleSheet(DESK_WIDGET);
}

InviteWidget::~InviteWidget() {
    //delete model;
}

void InviteWidget::buttonAccept() {
    deskAccept(this->id);
}

void InviteWidget::buttonCancel() {
    deskCancel(this->id);
}
