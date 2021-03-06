#include "deskmodel.h"
#include <QJsonArray>

DeskModel::DeskModel(QJsonObject obj) {
    this->id = obj["id"].toString();
    this->title = obj["title"].toString();
    this->description = obj["description"].toString();
    this->createdAt = obj["created_at"].toString();

    foreach (QJsonValue userValue, obj["users"].toArray()) {
        this->users.append(UserModel(userValue.toObject()));
    }

    foreach (QJsonValue cardValue, obj["cards"].toArray()) {
        this->cards.append(CardModel(cardValue.toObject()));
    }
}

QString DeskModel::getProgress() {
    int summCount = 0;
    int checkedCount = 0;
    foreach (CardModel card, cards) {
        summCount += card.getSummCount();
        checkedCount += card.getCheckedCount();
    }
    return QString::number(checkedCount) + "/" + QString::number(summCount);
}

DeskModel* DeskModel::check(QString id) {
    for(int i = 0; i < cards.size(); i++) {
        if (cards[i].check(id)) {
            break;
        }
    }
    return this;
}
