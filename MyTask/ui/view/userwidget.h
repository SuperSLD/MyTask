#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QFrame>
#include <QWidget>

#include <models/usermodel.h>

class UserWidget: public QFrame {
    Q_OBJECT
public:
    UserWidget(UserModel *user);
};

#endif // USERWIDGET_H
