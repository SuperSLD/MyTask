#include "mainfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QSvgWidget>
#include <QVBoxLayout>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonArray>
#include <QScrollArea>
#include <QScrollBar>

#include <ui/view/deskwidget.h>
using namespace screens;

MainFragment::MainFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *profileContainer = new QVBoxLayout;

    QPushButton *inviteButton = new QPushButton("Мои приглашения");
    QPushButton *addButton = new QPushButton("Создать доску");
    QPushButton *exitButton = new QPushButton("Выйти из профиля");

    QVBoxLayout *userContainer = new QVBoxLayout;
    QSvgWidget *profileImage = new QSvgWidget(":/resc/resc/user_circle.svg");
    QHBoxLayout *fuckContainer = new QHBoxLayout;
    userName = new QLabel("");

    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //deskScrollArea->setMaximumWidth(820);
    deskScrollArea->setMinimumWidth(820);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("scrollArea");
    QHBoxLayout *deskContainer = new QHBoxLayout;
    start = new QVBoxLayout;
    end = new QVBoxLayout;
    deskContainer->addLayout(start);
    deskContainer->addLayout(end);
    scrolContainer->setLayout(deskContainer);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);

    profileImage->setMaximumSize(QSize(100,100));
    profileImage->setContentsMargins(0,35,0,24);
    profileImage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    fuckContainer->addWidget(profileImage);
    userContainer->addLayout(fuckContainer);
    userName->setStyleSheet(TITLE_LABLE);
    userName->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    userName->setContentsMargins(35,0,35,24);
    userContainer->addWidget(userName);
    userContainer->setAlignment(Qt::AlignCenter);

    inviteButton->setStyleSheet(BUTTON_PROFILE);
    inviteButton->setMaximumWidth(270);
    inviteButton->setMinimumWidth(270);
    addButton->setStyleSheet(BUTTON_PROFILE);
    addButton->setMaximumWidth(270);
    addButton->setMinimumWidth(270);
    exitButton->setStyleSheet(BUTTON_PROFILE_RED);
    exitButton->setMaximumWidth(270);
    exitButton->setMinimumWidth(270);
    profileContainer->addLayout(userContainer);
    profileContainer->addWidget(inviteButton);
    profileContainer->addWidget(addButton);
    profileContainer->addWidget(exitButton);
    profileContainer->setAlignment(Qt::AlignTop);
    connect(inviteButton, &QPushButton::clicked, this, &MainFragment::onInvite);
    connect(addButton, &QPushButton::clicked, this, &MainFragment::onAdd);
    connect(exitButton, &QPushButton::clicked, this, &MainFragment::onExit);

    mainHLayout->addLayout(profileContainer);
    mainHLayout->addWidget(deskScrollArea);
    mainHLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainFragment::onHttpResult);
    loadData();
}

MainFragment::~MainFragment() {
    delete networkManager;
    delete userName;
    delete start;
    delete end;
}

void MainFragment::loadData() {
    QNetworkRequest request(QUrl(SERVER_URL + "/api/desk/mainPage"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    QNetworkReply* reply = networkManager->get(
        request
    );
    reply->setProperty("type", LIST);
}

void MainFragment::onExit() {
    QNetworkRequest request(QUrl(SERVER_URL + "/api/users/logout"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    QNetworkReply* reply = networkManager->post(
        request,
        ""
    );
    reply->setProperty("type", EXIT);
}

void MainFragment::onAdd() {

}

void MainFragment::onInvite() {

}

void MainFragment::onHttpResult(QNetworkReply *reply) {
    QString type = reply->property("type").toString();
    if(!reply->error()) {
        QByteArray resp = reply->readAll();
        qDebug() << resp << endl;
        QJsonDocument doc = QJsonDocument::fromJson(resp);
        QJsonObject obj;
        if(!doc.isNull()) {
            if(doc.isObject()) {
                obj = doc.object();
                qDebug() << obj["success"].toBool() << endl;
            }
            else {
                qDebug() << "Document is not an object" << endl;
            }
        } else {
            qDebug() << "Invalid JSON...\n" << endl;
        }
        if (obj["success"].toBool()) {
            if (type == EXIT) {
                QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
                settings->setValue("token", "");
                settings->sync();
                newRootScreen(START_TAG);
            } else if (type == LIST) {
                userName->setText("@"+
                        obj["data"]
                        .toObject()["user"]
                        .toObject()["name"]
                        .toString());
                parseDeskList(obj["data"]
                        .toObject()["items"].toArray());

            }
        } else {
            qDebug("login error");
            QMessageBox::warning(this, "Ошибка", obj["message"].toString());
        }
    } else {
        QMessageBox::warning(this, "Ошибка",
            "При подключениии произошла ошибка.\n"        );
    }
    reply->deleteLater();
}

void MainFragment::parseDeskList(QJsonArray items) {
    foreach(QJsonValue deskValue, items) {
        deskList.append(DeskModel(deskValue.toObject()));
        DeskWidget *deskWidget = new DeskWidget(deskList.last());
        if (deskList.size() % 2 == 1) {
            start->addWidget(deskWidget);
        } else {
            end->addWidget(deskWidget);
        }
    }
}
