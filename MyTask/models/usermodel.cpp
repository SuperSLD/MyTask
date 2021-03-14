#include "usermodel.h"

UserModel::UserModel(QJsonObject obj) {
    this->id = obj["id"].toString();
    this->name = obj["name"].toString();
    this->image = obj["image"].toString();
}
