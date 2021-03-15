#ifndef DESKMODEL_H
#define DESKMODEL_H

#include "basemodel.h"
#include "cardmodel.h"
#include "usermodel.h"

#include <QJsonObject>
#include <QString>
#include <QList>

class DeskModel: public BaseModel {
public:
    DeskModel(QJsonObject obj);

    QString id;
    QString title;
    QString description;
    QString createdAt;
    QList<UserModel> users;
    QList<CardModel> cards;

    QString getProgress();
};

#endif // DESKMODEL_H
