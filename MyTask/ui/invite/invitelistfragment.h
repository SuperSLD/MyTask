#ifndef INVITELISTFRAGMENT_H
#define INVITELISTFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <models/deskmodel.h>
#include <ui/view/waitingspinnerwidget.h>

class InviteListFragment: public BaseFragment {
    Q_OBJECT
private:
    QNetworkAccessManager *networkManager;
    QString token;
    QString lastRequest;

    QList<DeskModel> deskList;
    QLabel *userName;

    WaitingSpinnerWidget *loading;

    QVBoxLayout *start;
    QVBoxLayout *end;

    const QString LIST = "req_list";
    const QString ACCEPT = "req_accept";
    const QString CANCEL = "req_cancel";

    void loadData();
    void parseDeskList(QJsonArray items);

    int getCardH(QVBoxLayout *container);
    void clearLayout(QVBoxLayout *container);
public:
    InviteListFragment();
    ~InviteListFragment();

public slots:
    void onCancel(QString id);
    void onAccept(QString id);

    void onBackPressed();

    void onHttpResult(QNetworkReply *reply);
};
#endif // INVITELISTFRAGMENT_H
