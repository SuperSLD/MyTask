#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <models/deskmodel.h>

class MainFragment: public BaseFragment {
    Q_OBJECT
private:
    QNetworkAccessManager *networkManager;
    QString token;
    QString lastRequest;

    QList<DeskModel> deskList;
    QLabel *userName;

    QVBoxLayout *start;
    QVBoxLayout *end;

    const QString EXIT = "req_exit";
    const QString LIST = "req_list";

    void loadData();
    void parseDeskList(QJsonArray items);

    int getCardH(QVBoxLayout *container);

public:
    MainFragment();
    ~MainFragment();

public slots:
    void onExit();
    void onAdd();
    void onInvite();

    void onHttpResult(QNetworkReply *reply);
};

#endif // MAINFRAGMENT_H
