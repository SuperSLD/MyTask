#ifndef USERMODEL_H
#define USERMODEL_H

#include "basemodel.h"

#include <QJsonObject>



class UserModel: public BaseModel {
public:
    UserModel(QJsonObject obj);

    QString id;
    QString name;
    QString image;
};

#endif // USERMODEL_H
