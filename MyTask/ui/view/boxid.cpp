#include "boxid.h"

BoxId::BoxId(QString id) {
    this->id = id;
    this->setStyleSheet("background-color: #E6EBF0;");
    connect(this, &BoxId::clicked, this, &BoxId::checkClick);
}

void BoxId::checkClick() {
    clickCheckbox(this->id);
}
