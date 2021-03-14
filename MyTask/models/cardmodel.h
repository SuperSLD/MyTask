#ifndef CARDMODEL_H
#define CARDMODEL_H

#include "checkboxmodel.h"

#include <QJsonObject>
#include <QList>

class CardModel
{
public:
    CardModel(QJsonObject obj);

    QString id;
    QString title;
    QString description;
    QString type;
    QList<CheckBoxModel> checkbox;
};

#endif // CARDMODEL_H
