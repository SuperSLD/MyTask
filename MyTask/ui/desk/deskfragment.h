#ifndef DESKFRAGMENT_H
#define DESKFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QScrollBar>
#include <QVBoxLayout>

#include <models/cardmodel.h>
#include <models/deskmodel.h>
#include <ui/view/boxid.h>

class DeskFragment: public BaseFragment {
    Q_OBJECT
private:
    QLabel *titleLabel;
    QLabel *description;
    QLabel *users;
    QLabel *progress;

    const QString LOAD_DATA = "load_data";

    DeskModel *model;
    QNetworkAccessManager *networkManager;

    QString token;

    QVBoxLayout *cards;
public:
    DeskFragment();
    ~DeskFragment();

    void onResume() override;

    void loadData();
    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();
    void onCreateCard();
    void onCheckCliced();

    void onHttpResult(QNetworkReply *reply);
    void clickBox(QString id);
};

#endif // DESKFRAGMENT_H
