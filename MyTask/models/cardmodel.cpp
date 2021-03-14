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
