#ifndef USERSLISTFRAGMENT_H
#define USERSLISTFRAGMENT_H

#include <QLabel>
#include <QWidget>

#include <common/base/basefragment.h>

#include <models/deskmodel.h>

class UsersListFragment: public BaseFragment {
    Q_OBJECT
private:
    QLabel *titleLabel;
    QLabel *description;

    const QString LOAD_DATA = "load_data";

    DeskModel *model;

    QString token;

    QVBoxLayout *cards;
public:
    UsersListFragment();
    ~UsersListFragment();

    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();
    void onCreateInvite();
};

#endif // USERSLISTFRAGMENT_H
