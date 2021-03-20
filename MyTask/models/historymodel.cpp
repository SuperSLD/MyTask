#include "historymodel.h"

#include <QJsonObject>



HistoryModel::HistoryModel(QJsonObject obj) {
    this->id = obj["id"].toString();
    this->deskId = obj["desk_id"].toString();
    this->message = obj["message"].toString();
    this->createdAt = obj["created_at"].toString();
    this->user = new UserModel(obj["user"].toObject());
}

HistoryModel::~HistoryModel() {

}
