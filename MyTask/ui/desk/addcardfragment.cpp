#include "addcardfragment.h"

#include <QLabel>
#include <QSettings>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <ui/view/qsvgbutton.h>
#include <QMessageBox>
#include <QNetworkReply>

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"
using namespace screens;

AddCardFragment::AddCardFragment() {
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    token = settings->value("token", "").toString();

    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QVBoxLayout *inputContainer = new QVBoxLayout;

    QHBoxLayout *titleContainer = new QHBoxLayout;
    QSvgButton *backButton = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));
    QLabel *titleLabel = new QLabel("Добавление карточки");

    QHBoxLayout *buttoContainer = new QHBoxLayout;
    createButton = new QPushButton("Добавить карточку");

    titleEdit = new QLineEdit;
    descriptionEdit = new QPlainTextEdit;

    titleLabel->setStyleSheet(TITLE_LABLE);
    connect(backButton, &QSvgButton::clicked, this, &AddCardFragment::onBackPressed);
    titleContainer->addWidget(backButton);
    titleContainer->addWidget(titleLabel);
    titleContainer->setContentsMargins(0,24,0,16);
    titleLabel->setContentsMargins(16,0,0,0);

    titleEdit->setMaximumWidth(574);
    titleEdit->setStyleSheet(EDIT_TEXT);
    titleEdit->setPlaceholderText("Название карточки");
    descriptionEdit->setMaximumWidth(574);
    descriptionEdit->setStyleSheet(EDIT_TEXT);
    descriptionEdit->setPlaceholderText("Описание карточки");
    descriptionEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    connect(titleEdit, &QLineEdit::textChanged, this, &AddCardFragment::checkData);
    connect(descriptionEdit, &QPlainTextEdit::textChanged, this, &AddCardFragment::checkData);

    createButton->setStyleSheet(BUTTON_SOLID);
    createButton->setMaximumWidth(335);
    createButton->setMinimumWidth(335);
    connect(createButton, &QPushButton::clicked, this, &AddCardFragment::onCreatePressed);
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
    connect(networkManager, &QNetworkAccessManager::finished, this, &AddCardFragment::onHttpResult);
}

AddCardFragment::~AddCardFragment() {
    delete titleEdit;
    delete descriptionEdit;
    delete createButton;
    //delete networkManager;
}

void AddCardFragment::checkData() {
    if (titleEdit->text().length() > 2 && descriptionEdit->toPlainText().length() > 10) {
        createButton->setStyleSheet(BUTTON_SOLID);
    } else {
        createButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void AddCardFragment::setData(BaseModel *model) {
    DeskModel *desk = dynamic_cast<DeskModel*>(model);
    this->model = desk;
}

void AddCardFragment::onBackPressed() {
    back();
}

void AddCardFragment::onCreatePressed() {
    if (titleEdit->text().length() > 2 && descriptionEdit->toPlainText().length() > 10) {
        QJsonObject param;
        param.insert("desk_id", this->model->id);
        param.insert("title", titleEdit->text());
        param.insert("description", descriptionEdit->toPlainText());
        param.insert("type_card", "simple");
        QNetworkRequest request(QUrl(SERVER_URL + "/api/desk/createCard"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        request.setRawHeader("Authorization", ("Bearer " + token).toLocal8Bit());
        networkManager->post(
            request,
            QJsonDocument(param).toJson(QJsonDocument::Compact)
        );
    }
}

void AddCardFragment::onHttpResult(QNetworkReply *reply) {
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
