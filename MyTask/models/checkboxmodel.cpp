#include "checkboxmodel.h"

CheckBoxModel::CheckBoxModel(QJsonObject obj) {
    this->id = obj["id"].toString();
    this->title = obj["title"].toString();
    this->checked = obj["checked"].toBool();
}
