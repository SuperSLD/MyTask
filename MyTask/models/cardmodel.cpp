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
        for (int i = 0; i < checkbox.size(); i++) {
            if (checkbox[i].id == id) {
                clickCount++;
                qDebug("box id = " + id.toLatin1());
                qDebug("box find and check [count = "+QString::number(clickCount).toLatin1()+"]");
                if (checkbox[i].checked) {
                    qDebug("checked");
                    checkbox[i].checked = false;
                } else {
                    qDebug("unchecked");
                    checkbox[i].checked = true;
                }
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}
