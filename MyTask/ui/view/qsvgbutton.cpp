#include "qsvgbutton.h"

#include <QSvgWidget>
#include <QVBoxLayout>

QSvgButton::QSvgButton(QString path, QSize size) {
    QVBoxLayout *mainContainer = new QVBoxLayout;
    QSvgWidget *image = new QSvgWidget(path);
    image->setMaximumSize(size);
    image->setMinimumSize(size);
    mainContainer->addWidget(image);
    mainContainer->setContentsMargins(0,0,0,0);
    image->setStyleSheet("background-color:#FFFFFF;");
    this->setStyleSheet("border:none; padding:0px; background-color:#FFFFFF;");
    this->setMinimumSize(size);
    this->setMaximumSize(size);
    this->setLayout(mainContainer);
}

QSvgButton::~QSvgButton() {

}
