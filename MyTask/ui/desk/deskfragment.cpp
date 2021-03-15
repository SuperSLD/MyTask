#include "deskfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "adddeskfragment.h"
#include "screensfactory.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QSettings>
#include <QCheckBox>

#include <models/cardmodel.h>

#include <ui/view/linewidget.h>
#include <ui/view/qsvgbutton.h>

#include <models/deskmodel.h>
using namespace screens;

DeskFragment::DeskFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *infoContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    titleLabel = new QLabel("Доска");
    description = new QLabel();
    users = new QLabel();
    progress = new QLabel();

    QHBoxLayout *buttonContainer = new QHBoxLayout;
    QPushButton *usersButton = new QPushButton("Пользователи");
    QPushButton *addButton = new QPushButton("Добавить");

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

    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);
    titleLabel->setWordWrap(true);
    titleLabel->setMinimumWidth(325);
    titleLabel->setMaximumWidth(325);
    titleLabel->setMaximumWidth(325-24-16);
    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &DeskFragment::onBackPressed);

    description->setStyleSheet(TEXT_DARK_LABLE);
    description->setWordWrap(true);
    description->setMaximumWidth(325);
    description->setMinimumWidth(325);
    users->setContentsMargins(0,8,0,8);
    users->setStyleSheet(TEXT_PRIMARY_16PX_LABLE);
    users->setWordWrap(true);
    users->setMaximumWidth(325);
    progress->setStyleSheet(TEXT_HINT_16PX_LABLE);
    progress->setWordWrap(true);
    progress->setMaximumWidth(325);
    progress->setContentsMargins(0,0,0,8);

    usersButton->setStyleSheet(BUTTON_EMPTY);
    addButton->setStyleSheet(BUTTON_SOLID);
    buttonContainer->addWidget(usersButton);
    buttonContainer->addWidget(addButton);

    infoContainer->setAlignment(Qt::AlignTop);
    infoContainer->addLayout(titleContainer);
    infoContainer->addWidget(description);
    infoContainer->addWidget(users);
    infoContainer->addWidget(progress);
    infoContainer->addLayout(buttonContainer);

    mainHLayout->addLayout(infoContainer);
    mainHLayout->addWidget(deskScrollArea);
    mainHLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");
}

DeskFragment::~DeskFragment() {
    delete titleLabel;
    delete users;
    delete progress;
    delete description;
}

void DeskFragment::setData(BaseModel *model) {
    DeskModel *desk = dynamic_cast<DeskModel*>(model);

    titleLabel->setText(desk->title);
    description->setText(desk->description);
    users->setText(QString::number(desk->users.length()) + " участников");
    progress->setText(desk->getProgress() + " пунктов выполнено");

    QLabel *scrollTitle = new QLabel("Карточки:");
    LineWidget *line = new LineWidget;

    scrollTitle->setStyleSheet(TEXT_HINT_18PX_LABLE);

    cards->addWidget(scrollTitle);
    cards->addWidget(line);

    QList<CardModel> cardList = desk->cards;
    foreach (CardModel card, cardList) {
        QVBoxLayout *cardContainer = new QVBoxLayout;
        cardContainer->setContentsMargins(24,24,24,24);
        QLabel *cardTitle = new QLabel(card.title);
        cardTitle->setMinimumWidth(396-24-24);
        cardTitle->setMaximumWidth(396-24-24);
        cardTitle->setWordWrap(true);
        cardTitle->setStyleSheet(TEXT_DARK_18PX_LABLE);

        QLabel *cardDescription = new QLabel(card.description);
        cardDescription->setMinimumWidth(396-24-24);
        cardDescription->setMaximumWidth(396-24-24);
        cardDescription->setWordWrap(true);
        cardDescription->setStyleSheet(TEXT_DARK_LABLE);

        cardContainer->addWidget(cardTitle);
        cardContainer->addWidget(cardDescription);

        /*
        if (card.type == "checkbox") {
            QFrame *checkBoxContainer = new QFrame;
            QVBoxLayout *checkboxLayout = new QVBoxLayout;
            foreach (CheckBoxModel box, card.checkbox) {
                QCheckBox *checkboxWidget = new QCheckBox(box.title);
                checkboxWidget->setChecked(box.checked);
                checkboxWidget->setStyleSheet(TEXT_DARK_LABLE);
                checkboxWidget->setContentsMargins(0,4,0,0);
                checkboxWidget->setMinimumHeight(24);

                checkboxLayout->addWidget(checkboxWidget);
            }
            checkBoxContainer->setLayout(checkboxLayout);
            cardContainer->addWidget(checkBoxContainer);
        }*/

        cards->addLayout(cardContainer);
        cards->addWidget(new LineWidget);
    }
}

void DeskFragment::onBackPressed() {
    back();
}
