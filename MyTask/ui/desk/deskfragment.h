#ifndef DESKFRAGMENT_H
#define DESKFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLabel>
#include <QScrollBar>
#include <QVBoxLayout>

#include <models/cardmodel.h>

class DeskFragment: public BaseFragment {
    Q_OBJECT
private:
    QLabel *titleLabel;
    QLabel *description;
    QLabel *users;
    QLabel *progress;

    QString token;

    QVBoxLayout *cards;
public:
    DeskFragment();
    ~DeskFragment();

    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();
};

#endif // DESKFRAGMENT_H
