#ifndef HISTORYMODEL_H
#define HISTORYMODEL_H

#include "basemodel.h"
#include "usermodel.h"

#include <QJsonObject>



class HistoryModel: BaseModel {
public:
    QString id;
    QString deskId;
    QString message;
    QString createdAt;
    UserModel *user;

    HistoryModel(QJsonObject obj);
    ~HistoryModel();
};

#endif // HISTORYMODEL_H
