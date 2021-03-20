#include "invitelistfragment.h"

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
#include <ui/view/invitewidget.h>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

InviteListFragment::InviteListFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Приглашения");
    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &InviteListFragment::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);

    mainVLayout->addLayout(titleContainer);

    userName = new QLabel("");

    QScrollArea *deskScrollArea = new QScrollArea;
    //deskScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    deskScrollArea->setMinimumWidth(820);
    deskScrollArea->setMaximumWidth(820);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;

    loading = new WaitingSpinnerWidget(scrolContainer, true, false);
    loading->setColor(QT_COLOR_PRIMARY);

    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *deskContainer = new QHBoxLayout;
    start = new QVBoxLayout;
    start->setAlignment(Qt::AlignTop);
    end = new QVBoxLayout;
    end->setAlignment(Qt::AlignTop);
    deskContainer->addLayout(start);
    deskContainer->addLayout(end);
    scrolContainer->setLayout(deskContainer);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);

    mainVLayout->addWidget(deskScrollArea);
    mainVLayout->setAlignment(Qt::AlignTop);
    mainHLayout->addLayout(mainVLayout);
    mainHLayout->setAlignment(Qt::AlignHCenter);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &InviteListFragment::onHttpResult);
    loadData();
}

InviteListFragment::~InviteListFragment() {
    delete networkManager;
    delete userName;
    delete start;
    delete end;
    delete loading;
}

void InviteListFragment::loadData() {
    loading->start();
    QNetworkRequest request(QUrl(SERVER_URL + "/api/invite/list"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    QNetworkReply* reply = networkManager->get(
        request
    );
    reply->setProperty("type", LIST);
}

void InviteListFragment::onCancel(QString id) {
    QNetworkRequest request(QUrl(SERVER_URL + "/api/invite/cancel/" + id));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    QNetworkReply* reply = networkManager->get(
        request
    );
    reply->setProperty("type", CANCEL);
}

void InviteListFragment::onAccept(QString id) {
    QNetworkRequest request(QUrl(SERVER_URL + "/api/invite/accept/" + id));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    QNetworkReply* reply = networkManager->get(
        request
    );
    reply->setProperty("type", ACCEPT);
}

void InviteListFragment::onHttpResult(QNetworkReply *reply) {
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
            if (type == ACCEPT || type == CANCEL) {
                loadData();
            } else if (type == LIST) {
                parseDeskList(obj["data"].toArray());
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

void InviteListFragment::parseDeskList(QJsonArray items) {
    loading->stop();
    clearLayout(start);
    clearLayout(end);
    deskList.clear();
    foreach(QJsonValue deskValue, items) {
        deskList.append(DeskModel(deskValue["desk"].toObject()));
        qDebug("add invite -> " + deskValue["id"].toString().toLatin1());
        InviteWidget *deskWidget = new InviteWidget(
                    &deskList.last(),
                    deskValue["id"].toString()
        );
        connect(deskWidget, &InviteWidget::deskCancel, this, &InviteListFragment::onCancel);
        connect(deskWidget, &InviteWidget::deskAccept, this, &InviteListFragment::onAccept);
        if (getCardH(start) <= getCardH(end)) {
            start->addWidget(deskWidget);
        } else {
            end->addWidget(deskWidget);
        }
    }
}

int InviteListFragment::getCardH(QVBoxLayout *container) {
    int h = 0;
    for (int i = 0; i < container->count(); i++) {
        h += container->itemAt(i)->widget()->geometry().height();
    }
    return h;
}

void InviteListFragment::onBackPressed() {
    back();
}

void InviteListFragment::clearLayout(QVBoxLayout *container) {
    QLayoutItem* item;
    while ( ( item = container->layout()->takeAt( 0 ) ) != NULL ) {
        delete item->widget();
        delete item;
    }
}
