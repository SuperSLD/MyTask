#include "addcardfragment.h"

#include <QLabel>
#include <QSettings>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>
#include <QJsonArray>
#include <QMessageBox>
#include <QNetworkReply>
#include <QScrollArea>
#include <QScrollBar>
#include <QSvgWidget>
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
    QHBoxLayout *buttonBoxContainer = new QHBoxLayout;
    createButton = new QPushButton("Добавить карточку");
    createBoxButton = new QPushButton("Добавить карточку");

    QFrame *loadingContaiter = new QFrame;
    loading = new WaitingSpinnerWidget(loadingContaiter, true, false);
    loading->setColor(QT_COLOR_PRIMARY);
    loadingContaiter->setMinimumWidth(100);

    titleEdit = new QLineEdit;
    descriptionEdit = new QPlainTextEdit;

    QScrollArea *deskScrollArea = new QScrollArea;
    deskScrollArea->setMinimumWidth(396);
    deskScrollArea->setFrameShape(QFrame::NoFrame);
    QWidget *scrolContainer = new QWidget;
    scrolContainer->setObjectName("container");
    scrolContainer->setStyleSheet(GLOBAL_BACK_WHITE);
    deskScrollArea->setStyleSheet(SCROL_BAR);
    QHBoxLayout *content = new QHBoxLayout;
    content->setAlignment(Qt::AlignHCenter);
    scrolContainer->setLayout(content);
    deskScrollArea->setWidget(scrolContainer);
    deskScrollArea->setWidgetResizable(true);
    deskScrollArea->horizontalScrollBar()->setEnabled(false);

    // селектор типа карточки
    QHBoxLayout *selectorContainer = new QHBoxLayout;
    simpleButtom = new QPushButton("Текст");
    boxButton = new QPushButton("Чекбокс");
    simpleButtom->setStyleSheet(BUTTON_SOLID);
    boxButton->setStyleSheet(BUTTON_DISABLED);
    selectorContainer->addWidget(simpleButtom);
    selectorContainer->addWidget(boxButton);
    connect(simpleButtom, &QPushButton::clicked, this, &AddCardFragment::onText);
    connect(boxButton, &QPushButton::clicked, this, &AddCardFragment::onBox);

    //стак для выбора контента
    stack = new QStackedWidget;
    stack->setMaximumWidth(574);
    stack->setMinimumWidth(574);
    QFrame *textWidget = new QFrame;
    QVBoxLayout *textLayout = new QVBoxLayout;
    QFrame *boxWidget = new QFrame;
    QVBoxLayout *boxLayout = new QVBoxLayout;
    textWidget->setLayout(textLayout);
    textLayout->setAlignment(Qt::AlignTop);
    boxWidget->setLayout(boxLayout);
    boxLayout->setAlignment(Qt::AlignTop);
    stack->addWidget(textWidget);
    stack->addWidget(boxWidget);
    stack->setCurrentIndex(0);
    stack->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // стак для обычной карточки
    QLabel *textDesctiption = new QLabel("Самый просой тип карточки который содержит только текст и больше ничего. Полезен когда нужно оставить обычную заметку.");
    textDesctiption->setStyleSheet(TEXT_HINT_LABLE);
    textDesctiption->setContentsMargins(0,24,0,16);
    textDesctiption->setWordWrap(true);
    textLayout->setContentsMargins(0,0,0,0);
    textLayout->addWidget(textDesctiption);
    textLayout->addLayout(buttoContainer);

    // стак для карточки с чекбоксами
    QLabel *textBoxDesctiption = new QLabel("Карточка с чекбоксами, основной тип карточкек. По этим карточкам идет подсчет прогресса всей доски.");
    cardTitleEdit = new QLineEdit;
    connect(cardTitleEdit, &QLineEdit::textChanged, this, &AddCardFragment::checkBoxTitle);
    QHBoxLayout *titleEditContainer = new QHBoxLayout;
    addBoxTitleButton = new QSvgButton(":/resc/resc/done_outline.svg", QSize(24,24));
    titleWidgetList = new QVBoxLayout;
    titleWidgetList->setAlignment(Qt::AlignTop);
    connect(addBoxTitleButton, &QSvgButton::clicked, this, &AddCardFragment::onBoxTitleAdd);
    addBoxTitleButton->hide();
    cardTitleEdit->setMaximumWidth(574);
    cardTitleEdit->setStyleSheet(EDIT_TEXT);
    cardTitleEdit->setPlaceholderText("Текст чекбокса");
    textBoxDesctiption->setStyleSheet(TEXT_HINT_LABLE);
    textBoxDesctiption->setContentsMargins(0,24,0,16);
    textBoxDesctiption->setWordWrap(true);
    titleEditContainer->addWidget(cardTitleEdit);
    titleEditContainer->addWidget(addBoxTitleButton);
    boxLayout->setContentsMargins(0,0,0,0);
    boxLayout->addWidget(textBoxDesctiption);
    boxLayout->addLayout(titleWidgetList);
    boxLayout->addLayout(titleEditContainer);
    boxLayout->addLayout(buttonBoxContainer);

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
    buttoContainer->addWidget(loadingContaiter);
    buttoContainer->addWidget(createButton);
    buttoContainer->setAlignment(Qt::AlignRight);

    createBoxButton->setStyleSheet(BUTTON_SOLID);
    createBoxButton->setMaximumWidth(335);
    createBoxButton->setMinimumWidth(335);
    connect(createBoxButton, &QPushButton::clicked, this, &AddCardFragment::onCreatePressed);
    buttonBoxContainer->addWidget(createBoxButton);
    buttonBoxContainer->setAlignment(Qt::AlignRight);

    inputContainer->setAlignment(Qt::AlignTop);
    inputContainer->addLayout(titleContainer);
    inputContainer->addWidget(titleEdit);
    inputContainer->addWidget(descriptionEdit);
    inputContainer->addLayout(selectorContainer);
    inputContainer->addWidget(stack);

    content->addLayout(inputContainer);

    mainHLayout->setAlignment(Qt::AlignHCenter);
    mainHLayout->addWidget(deskScrollArea);

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
    delete simpleButtom;
    delete boxButton;
    delete loading;
    //delete networkManager;
}

void AddCardFragment::checkData() {
    if (titleEdit->text().length() > 2 && descriptionEdit->toPlainText().length() > 10) {
        createButton->setStyleSheet(BUTTON_SOLID);
    } else {
        createButton->setStyleSheet(BUTTON_DISABLED);
    }
    if (titleEdit->text().length() > 2
            && descriptionEdit->toPlainText().length() > 10
            && titleList.size() > 0) {
        createBoxButton->setStyleSheet(BUTTON_SOLID);
    } else {
        createBoxButton->setStyleSheet(BUTTON_DISABLED);
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
        createButton->setDisabled(true);
        loading->show();
        createButton->setStyleSheet(BUTTON_DISABLED);
        QJsonObject param;
        param.insert("desk_id", this->model->id);
        param.insert("title", titleEdit->text());
        param.insert("description", descriptionEdit->toPlainText());
        param.insert("type_card", this->currentType);
        if (this->currentType == "checkbox") {
            QJsonArray checkbox = *new QJsonArray;
            foreach (QString title, this->titleList) {
                checkbox.append(title);
            }
            param.insert("checkbox", QJsonValue(checkbox));
        }
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
    createButton->setDisabled(false);
    loading->stop();
    createButton->setStyleSheet(BUTTON_SOLID);
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

void AddCardFragment::onText() {
    boxButton->setStyleSheet(BUTTON_DISABLED);
    simpleButtom->setStyleSheet(BUTTON_SOLID);
    stack->setCurrentIndex(0);
    this->currentType = "simple";
}

void AddCardFragment::onBox() {
    boxButton->setStyleSheet(BUTTON_SOLID);
    simpleButtom->setStyleSheet(BUTTON_DISABLED);
    stack->setCurrentIndex(1);
    this->currentType = "checkbox";
}

void AddCardFragment::checkBoxTitle() {
    if (cardTitleEdit->text().length() > 3) {
        addBoxTitleButton->show();
    } else {
        addBoxTitleButton->hide();
    }
}

void AddCardFragment::onBoxTitleAdd() {
    titleList.append(cardTitleEdit->text());
    QLabel *boxTitle = new QLabel(cardTitleEdit->text());
    boxTitle->setStyleSheet(TEXT_DARK_LABLE);
    QSvgWidget *mainImage = new QSvgWidget(":/resc/resc/done_outline.svg");
    mainImage->setMinimumSize(QSize(24,24));
    mainImage->setMaximumSize(QSize(24,24));
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(mainImage);
    container->addWidget(boxTitle);
    titleWidgetList->addLayout(container);
    cardTitleEdit->setText("");
    checkBoxTitle();
    checkData();
}
