#include "historyfragment.h"

#include "screensfactory.h"
#include "style/stylecontainer.h"

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
#include <QNetworkReply>


#include <ui/view/linewidget.h>
#include <ui/view/loadingwidget.h>
#include <ui/view/qsvgbutton.h>

using namespace styles;
using namespace screens;


HistoryFragment::HistoryFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *titleContainer = new QHBoxLayout;
    loading = new LoadingWidget;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("История действий");
    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &HistoryFragment::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);

    mainVLayout->addLayout(titleContainer);

    QScrollArea *deskScrollArea = new QScrollArea;
    //deskScrollArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    deskScrollArea->setMinimumWidth(574);
    deskScrollArea->setMaximumWidth(574);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *deskContainer = new QHBoxLayout;
    start = new QVBoxLayout;
    start->setAlignment(Qt::AlignTop);
    deskContainer->addLayout(start);
    start->setContentsMargins(0,0,0,0);
    scrolContainer->setLayout(deskContainer);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);
    deskScrollArea->verticalScrollBar()->hide();

    start->addWidget(loading);

    mainVLayout->addWidget(deskScrollArea);
    mainVLayout->setAlignment(Qt::AlignTop);
    mainHLayout->addLayout(mainVLayout);
    mainHLayout->setAlignment(Qt::AlignHCenter);


    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &HistoryFragment::onHttpResult);
}

void HistoryFragment::setData(BaseModel *model) {
    DeskModel *desk = dynamic_cast<DeskModel*>(model);
    this->model = desk;
    //loadData();
}

HistoryFragment::~HistoryFragment() {
    delete networkManager;
    delete start;
}

void HistoryFragment::parseHistoryList(QJsonArray items) {
    clearList(start);
    foreach(QJsonValue value, items) {
        HistoryModel historyLine = HistoryModel(value.toObject());
        historyList.append(historyLine);

        QVBoxLayout *messageContainer = new QVBoxLayout;
        QHBoxLayout *timestampContainer = new QHBoxLayout;
        QLabel *userNameLabel = new QLabel("@"+historyLine.user->name);
        QLabel *messageLabel = new QLabel(historyLine.message);
        QLabel *timestampLabel = new QLabel(historyLine.createdAt);

        userNameLabel->setStyleSheet(TEXT_PIMARY_18PX_LABLE);
        messageLabel->setStyleSheet(TEXT_DARK_LABLE);
        messageLabel->setWordWrap(true);
        timestampLabel->setStyleSheet(TEXT_HINT_16PX_LABLE);
        timestampContainer->addWidget(timestampLabel);
        timestampContainer->setContentsMargins(0,4,0,0);
        messageContainer->setContentsMargins(0,8,0,0);
        messageContainer->addWidget(messageLabel);
        timestampContainer->setAlignment(Qt::AlignRight);

        start->addWidget(userNameLabel);
        start->addLayout(messageContainer);
        start->addLayout(timestampContainer);
        start->addWidget(new LineWidget);
    }
}

void HistoryFragment::onBackPressed() {
    back();
}

void HistoryFragment::loadData() {
    QNetworkRequest request(QUrl(SERVER_URL + "/api/history/bydesk/" + model->id));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QStringLiteral("application/json;charset=utf-8"));
    request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
    networkManager->get(
        request
    );
}

void HistoryFragment::onHttpResult(QNetworkReply *reply) {
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
            parseHistoryList(obj["data"].toArray());
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
