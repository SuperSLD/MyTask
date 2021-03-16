#include "userslistfragment.h"

#include <ui/view/qsvgbutton.h>
#include <ui/view/userwidget.h>

#include <QScrollArea>
#include <QScrollBar>


#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"
using namespace screens;

UsersListFragment::UsersListFragment() {
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *infoContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Список участников");
    description = new QLabel("Добавляйте участников к доске, чтобы они тоже могли создавать карточки и менять их содержимое. Вместе работа над проектом будет проще.");

    QHBoxLayout *buttonContainer = new QHBoxLayout;
    QPushButton *addButton = new QPushButton("Пригласить");

    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    deskScrollArea->setMinimumWidth(396);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    cards = new QVBoxLayout;
    cards->setAlignment(Qt::AlignTop);
    scrolContainer->setLayout(cards);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);
    deskScrollArea->verticalScrollBar()->hide();

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);
    titleLabel->setWordWrap(true);
    titleLabel->setMinimumWidth(325);
    titleLabel->setMaximumWidth(325);
    titleLabel->setMaximumWidth(325-24-16);
    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &UsersListFragment::onBackPressed);

    description->setStyleSheet(TEXT_DARK_LABLE);
    description->setWordWrap(true);
    description->setMaximumWidth(325);
    description->setMinimumWidth(325);

    addButton->setStyleSheet(BUTTON_SOLID);
    buttonContainer->setContentsMargins(0,16,0,0);
    buttonContainer->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &UsersListFragment::onCreateInvite);

    infoContainer->setAlignment(Qt::AlignTop);
    infoContainer->addLayout(titleContainer);
    infoContainer->addWidget(description);
    infoContainer->addLayout(buttonContainer);

    mainHLayout->addLayout(infoContainer);
    mainHLayout->addWidget(deskScrollArea);
    mainHLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");
}

UsersListFragment::~UsersListFragment() {
    delete titleLabel;
    delete description;
}

void UsersListFragment::setData(BaseModel *model) {
    clearList(cards);
    DeskModel *desk = dynamic_cast<DeskModel*>(model);
    this->model = desk;

    foreach(UserModel user, desk->users) {
        cards->addWidget(new UserWidget(&user));
    }
}

void UsersListFragment::onBackPressed() {
    back();
}

void UsersListFragment::onCreateInvite() {
    navigateWhithData(CREATE_INVITE_TAG, model);
}
