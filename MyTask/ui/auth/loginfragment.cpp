#include "loginfragment.h"

#include <QJsonValue>
#include <QLabel>
#include <QPushButton>
#include <QSvgWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <ui/view/qsvgbutton.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QSettings>

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"
using namespace screens;

LoginFragment::LoginFragment() {
    qDebug("SplashFragnebt crete");

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QFrame *centerConainer = new QFrame;

    QVBoxLayout *startMainLayout = new QVBoxLayout;
    QHBoxLayout *startContent = new QHBoxLayout;
    QSvgWidget *mainImage = new QSvgWidget(":/resc/resc/finances.svg");

    QVBoxLayout *backContainer = new QVBoxLayout;
    QSvgButton *backImage = new QSvgButton(":/resc/resc/arrow_back.svg", QSize(24,24));


    QVBoxLayout *startVerticalContent = new QVBoxLayout;
    QLabel *title = new QLabel("Вход в приложение");
    QLabel *subtitle = new QLabel("Не сообщяйте никому свои данные для авторизации.");
    loginEdit = new QLineEdit;
    passwordEdit = new QLineEdit;

    QVBoxLayout *buttonContainer = new QVBoxLayout;

    loginButton = new QPushButton("Войти");

    title->setStyleSheet(TITLE_LABLE);
    subtitle->setStyleSheet(HINT_LABLE);
    subtitle->setMaximumWidth(335);
    subtitle->setMinimumWidth(335);
    subtitle->setWordWrap(true);
    startVerticalContent->addWidget(title);
    startVerticalContent->addWidget(subtitle);
    startVerticalContent->setAlignment(Qt::AlignTop);
    buttonContainer->setAlignment(Qt::AlignBottom);

    startMainLayout->addLayout(startVerticalContent);
    startMainLayout->addLayout(buttonContainer);

    loginEdit->setMaximumWidth(335);
    loginEdit->setStyleSheet(EDIT_TEXT);
    loginEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    loginEdit->setPlaceholderText("Логин");
    passwordEdit->setMaximumWidth(335);
    passwordEdit->setStyleSheet(EDIT_TEXT);
    passwordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    connect(loginEdit, &QLineEdit::textChanged, this, &LoginFragment::checkData);
    connect(passwordEdit, &QLineEdit::textChanged, this, &LoginFragment::checkData);

    loginButton->setStyleSheet(BUTTON_SOLID);
    connect(loginButton, &QPushButton::clicked, this, &LoginFragment::onLoginPressed);
    buttonContainer->addWidget(loginEdit);
    buttonContainer->addWidget(passwordEdit);
    buttonContainer->addWidget(loginButton);

    startContent->setContentsMargins(46,46,46,46);
    mainImage->setContentsMargins(0,0,56,0);
    mainImage->setMaximumSize(QSize(300, 300));
    backImage->setContentsMargins(-24, -24, 0, 0);
    backImage->setMaximumSize(QSize(24,24));
    backImage->setStyleSheet(BACK_WHITE);
    connect(backImage, &QSvgButton::clicked, this, &LoginFragment::onBackPressed);

    centerConainer->setStyleSheet(FRAME_8PX_WHITE);
    centerConainer->setLayout(startContent);
    mainImage->setStyleSheet(START_ICON);
    backContainer->addWidget(backImage);
    backContainer->setAlignment(Qt::AlignTop);
    startContent->addLayout(backContainer);
    startContent->addWidget(mainImage);
    startContent->addLayout(startMainLayout);

    mainHLayout->addWidget(centerConainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainVLayout);
    checkData();
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &LoginFragment::onHttpResult);
}

LoginFragment::~LoginFragment() {
    delete loginEdit;
    delete passwordEdit;
    delete loginButton;
    networkManager->clearAccessCache();
}

void LoginFragment::onLoginPressed() {
    QJsonObject param;
    param.insert("login", loginEdit->text());
    param.insert("password", passwordEdit->text());
    if (loginEdit->text().length() > 5 && passwordEdit->text().length() > 5) {
        qDebug() << "create request" << endl;
        QNetworkRequest request(QUrl(SERVER_URL + "/api/users/login"));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        qDebug() << "request data"<< QJsonDocument(param).toJson(QJsonDocument::Compact) << endl;
        networkManager->post(
            request,
            QJsonDocument(param).toJson(QJsonDocument::Compact)
        );
        qDebug() << "request send" << endl;
    }
}

void LoginFragment::onHttpResult(QNetworkReply *reply) {
    qDebug() << "http finished" << endl;
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
            QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
            QString token = obj["data"].toObject()["token"].toString();
            settings->setValue("token", token);
            settings->sync();
            newRootScreen(MAIN_TAG);
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

void LoginFragment::checkData() {
    if (loginEdit->text().length() > 5 && passwordEdit->text().length() > 5) {
        loginButton->setStyleSheet(BUTTON_SOLID);
    } else {
        loginButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void LoginFragment::onBackPressed() {
    back();
}
