#include "registrationfragment.h"

#include "style/stylecontainer.h"
using namespace styles;
#include "screensfactory.h"

#include <QSvgWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QSettings>
#include <QJsonObject>
#include <QMessageBox>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
using namespace screens;

RegistrationFragment::RegistrationFragment() {
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
    QLabel *title = new QLabel("Регистрация");
    QLabel *subtitle = new QLabel(
                "Придумайте себе пароль и логин для входа, "
                "чтобы мы могли вас узнавать на других устройствах.\n"
                "Логин и пароль должны быть длиннее пяти символов."
                );
    loginEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    inviteKeyEdit = new QLineEdit;

    QVBoxLayout *buttonContainer = new QVBoxLayout;

    QHBoxLayout *loadingButtonContainer = new QHBoxLayout;
    loadingContaiter = new QFrame;
    loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loading->setColor(QT_COLOR_PRIMARY);
    loadingContaiter->setMinimumWidth(100);
    loadingContaiter->hide();

    loginButton = new QPushButton("Создать профиль");

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

    inviteKeyEdit->setMaximumWidth(335);
    inviteKeyEdit->setStyleSheet(EDIT_TEXT);
    inviteKeyEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    inviteKeyEdit->setPlaceholderText("Ключ приглашения");
    loginEdit->setMaximumWidth(335);
    loginEdit->setStyleSheet(EDIT_TEXT);
    loginEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    loginEdit->setPlaceholderText("Логин");
    passwordEdit->setMaximumWidth(335);
    passwordEdit->setStyleSheet(EDIT_TEXT);
    passwordEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    connect(loginEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);
    connect(passwordEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);
    connect(inviteKeyEdit, &QLineEdit::textChanged, this, &RegistrationFragment::checkData);

    loginButton->setStyleSheet(BUTTON_SOLID);
    connect(loginButton, &QPushButton::clicked, this, &RegistrationFragment::onRegPressed);
    buttonContainer->addWidget(loginEdit);
    buttonContainer->addWidget(passwordEdit);
    buttonContainer->addWidget(inviteKeyEdit);
    loadingButtonContainer->addWidget(loginButton);
    loadingButtonContainer->addWidget(loadingContaiter);
    buttonContainer->addLayout(loadingButtonContainer);

    startContent->setContentsMargins(46,46,46,46);
    mainImage->setContentsMargins(0,0,56,0);
    mainImage->setMaximumSize(QSize(300, 300));
    backImage->setContentsMargins(-24, -24, 0, 0);
    backImage->setMaximumSize(QSize(24,24));
    backImage->setStyleSheet(BACK_WHITE);
    connect(backImage, &QSvgButton::clicked, this, &RegistrationFragment::onBackPressed);

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
    networkManager = new QNetworkAccessManager();
    connect(networkManager, &QNetworkAccessManager::finished, this, &RegistrationFragment::onRegResult);
    checkData();
}

RegistrationFragment::~RegistrationFragment() {
    delete loginEdit;
    delete passwordEdit;
    delete loginButton;
    delete networkManager;
    delete loading;
    delete loadingContaiter;
}

void RegistrationFragment::onRegPressed() {
    QJsonObject param;
    param.insert("login", loginEdit->text());
    param.insert("password", passwordEdit->text());
    if (loginEdit->text().length() > 5 && passwordEdit->text().length() > 5 && inviteKeyEdit->text().length() > 5) {
        loading->start();
        loadingContaiter->show();
        loginButton->setDisabled(true);
        loginButton->setStyleSheet(BUTTON_DISABLED);

        QNetworkRequest request(QUrl(SERVER_URL + "/api/users/registration/"+inviteKeyEdit->text()));
        request.setHeader(QNetworkRequest::ContentTypeHeader,
                          QStringLiteral("application/json;charset=utf-8"));
        networkManager->post(
            request,
            QJsonDocument(param).toJson(QJsonDocument::Compact)
        );
    }
}

void RegistrationFragment::onRegResult(QNetworkReply *reply) {
    loading->stop();
    loadingContaiter->hide();
    loginButton->setDisabled(false);
    checkData();

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

void RegistrationFragment::checkData() {
    if (loginEdit->text().length() > 5 && passwordEdit->text().length() > 5 && inviteKeyEdit->text().length() > 5) {
        loginButton->setStyleSheet(BUTTON_SOLID);
    } else {
        loginButton->setStyleSheet(BUTTON_DISABLED);
    }
}

void RegistrationFragment::onBackPressed() {
    back();
}
