#include "boxid.h"

BoxId::BoxId(QString id) {
    this->id = id;
    connect(this, &BoxId::clicked, this, &BoxId::checkClick);
}

void BoxId::checkClick() {
    clickCheckbox(this->id);
}
