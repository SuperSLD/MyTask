#ifndef CHECKBOXMODEL_H
#define CHECKBOXMODEL_H

#include <QJsonObject>



class CheckBoxModel
{
public:
    CheckBoxModel(QJsonObject obj);

    QString id;
    QString title;
    bool checked;
};

#endif // CHECKBOXMODEL_H
