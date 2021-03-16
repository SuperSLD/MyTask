#include "createinvitefragment.h"

#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QJsonObject>
#include <QNetworkReply>
#include <ui/view/qsvgbutton.h>
#include <QJsonDocument>
#include <QMessageBox>

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"
using namespace screens;

CreateInviteFragment::CreateInviteFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Создание приглашения");

    QVBoxLayout *desctiptionContainer = new QVBoxLayout;
    QLabel *description = new QLabel("Введите логин пользователя которому хотите отправить приглашение на участие в вашем проекте.");

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    createButton = new QPushButton("Отправить приглашение");

    titleEdit = new QLineEdit;

    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &CreateInviteFragment::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);

    titleEdit->setMaximumWidth(574);
    titleEdit->setStyleSheet(EDIT_TEXT);
    titleEdit->setPlaceholderText("Логин пользователя");
    connect(titleEdit, &QLineEdit::textChanged, this, &CreateInviteFragment::checkData);

    createButton->setStyleSheet(BUTTON_SOLID);
    createButton->setMaximumWidth(335);
    createButton->setMinimumWidth(335);
    connect(createButton, &QPushButton::clicked, this, &CreateInviteFragment::onCreatePressed);
    buttoContainer->addWidget(createButton);
    buttoContainer->setAlignment(Qt::AlignRight);

    description->setMaximumWidth(574);
    description->setMinimumWidth(574);
    description->setWordWrap(true);
    description->setStyleSheet(TEXT_DARK_LABLE);
    desctiptionContainer->setContentsMargins(0,8,0,8);
    desctiptionContainer->addWidget(description);

    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addWidget(titleEdit);
    inputContainer->addLayout(desctiptionContainer);
    inputContainer->addLayout(buttoContainer);
    mainHLayout->setAlignment(Qt::AlignHCenter);
    mainHLayout->addLayout(inputContainer);

    this->setLayout(mainHLayout);
    this->setStyleSheet(BACK_WHITE);
    this->setObjectName("fragment");

    checkData();

    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &CreateInviteFragment::onHttpResult);
}

CreateInviteFragment::~CreateInviteFragment() {
    delete titleEdit;
    delete createButton;
    networkManager->clearAccessCache();
}

void CreateInviteFragment::checkData() {
    if (titleEdit->text().length() > 5) {
        createButton->setStyleSheet(BUTTON_SOLID);
    } else {
        createButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void CreateInviteFragment::onBackPressed() {
    back();
}

void CreateInviteFragment::setData(BaseModel *model) {
    DeskModel *desk = dynamic_cast<DeskModel*>(model);
    this->model = desk;
}

void CreateInviteFragment::onCreatePressed() {
    if (titleEdit->text().length() > 5) {
        QJsonObject param;
        param.insert("login", titleEdit->text());
        param.insert("desk_id", model->id);
        QNetworkRequest request(QUrl(SERVER_URL + "/api/invite/send"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
        networkManager->post(
            request,
            QJsonDocument(param).toJson(QJsonDocument::Compact)
        );
    }
}

void CreateInviteFragment::onHttpResult(QNetworkReply *reply) {
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
