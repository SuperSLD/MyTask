#include "adddeskfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QLabel>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSettings>
#include <QMessageBox>

#include <ui/view/qsvgbutton.h>
using namespace screens;

AddDeskFragment::AddDeskFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Создание доски");

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    createButton = new QPushButton("Создать доску");

    titleEdit = new QLineEdit;
    descriptionEdit = new QPlainTextEdit;

    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &AddDeskFragment::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);

    titleEdit->setMaximumWidth(574);
    titleEdit->setStyleSheet(EDIT_TEXT);
    titleEdit->setPlaceholderText("Логин");
    descriptionEdit->setMaximumWidth(574);
    descriptionEdit->setStyleSheet(EDIT_TEXT);
    descriptionEdit->setPlaceholderText("Пароль");
    descriptionEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    connect(titleEdit, &QLineEdit::textChanged, this, &AddDeskFragment::checkData);
    connect(descriptionEdit, &QPlainTextEdit::textChanged, this, &AddDeskFragment::checkData);

    createButton->setStyleSheet(BUTTON_SOLID);
    createButton->setMaximumWidth(335);
    createButton->setMinimumWidth(335);
    connect(createButton, &QPushButton::clicked, this, &AddDeskFragment::onCreatePressed);
    buttoContainer->addWidget(createButton);
    buttoContainer->setAlignment(Qt::AlignRight);

    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addWidget(titleEdit);
    inputContainer->addWidget(descriptionEdit);
    inputContainer->addLayout(buttoContainer);
    mainHLayout->setAlignment(Qt::AlignHCenter);
    mainHLayout->addLayout(inputContainer);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &AddDeskFragment::onHttpResult);
}

AddDeskFragment::~AddDeskFragment() {
    delete titleEdit;
    delete descriptionEdit;
    delete createButton;
    networkManager->clearAccessCache();
}

void AddDeskFragment::checkData() {
    if (titleEdit->text().length() > 2 && descriptionEdit->toPlainText().length() > 10) {
        createButton->setStyleSheet(BUTTON_SOLID);
    } else {
        createButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void AddDeskFragment::onBackPressed() {
    back();
}

void AddDeskFragment::onCreatePressed() {
    if (titleEdit->text().length() > 2 && descriptionEdit->toPlainText().length() > 10) {
        QJsonObject param;
        param.insert("title", titleEdit->text());
        param.insert("description", descriptionEdit->toPlainText());
        QNetworkRequest request(QUrl(SERVER_URL + "/api/desk/create"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
        networkManager->post(
            request,
            QJsonDocument(param).toJson(QJsonDocument::Compact)
        );
    }
}

void AddDeskFragment::onHttpResult(QNetworkReply *reply) {
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
               back();
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