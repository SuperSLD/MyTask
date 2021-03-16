#include "cardmodel.h"
#include <QJsonArray>

CardModel::CardModel(QJsonObject obj) {
    this->id = obj["id"].toString();
    this->title = obj["title"].toString();
    this->description = obj["description"].toString();
    this->type = obj["type"].toString();

    if (type == "checkbox") {
        foreach (QJsonValue checkValue, obj["checkbox"].toArray()) {
            this->checkbox.append(CheckBoxModel(checkValue.toObject()));
        }
    }
}

int CardModel::getCheckedCount() {
    int checked = 0;
    if (type == "checkbox") {
        foreach (CheckBoxModel box, checkbox) {
            if (box.checked) {
                checked++;
            }
        }
    }
    return checked;
}

int CardModel::getSummCount() {
    if (type == "checkbox") {
        return this->checkbox.length();
    } else {
        return 0;
    }
}

bool CardModel::check(QString id) {
    if (this->type == "checkbox") {
        foreach (CheckBoxModel box, this->checkbox) {
            if (box.id == id) {
                clickCount++;
                qDebug("box find and check [count = "+QString::number(clickCount).toLatin1()+"]");
                if (box.checked) {
                    qDebug("checked");
                    box.checked = false;
                } else {
                    qDebug("unchecked");
                    box.checked = true;
                }
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}
