#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QVBoxLayout>
#include <models/deskmodel.h>
#include <ui/view/waitingspinnerwidget.h>

class MainFragment: public BaseFragment {
    Q_OBJECT
private:
    QNetworkAccessManager *networkManager;
    QString token;
    QString lastRequest;

    QPushButton *exitButton;

    QList<DeskModel*> deskList;
    QLabel *userName;

    QVBoxLayout *start;
    QVBoxLayout *end;

    WaitingSpinnerWidget *loading;
    WaitingSpinnerWidget *loadingExit;


    const QString EXIT = "req_exit";
    const QString LIST = "req_list";

    void loadData();
    void parseDeskList(QJsonArray items);

    int getCardH(QVBoxLayout *container);
    void clearLayout(QVBoxLayout *container);

public:
    MainFragment();
    ~MainFragment();

    void onResume() override;
public slots:
    void onExit();
    void onAdd();
    void onInvite();

    void deskSelected(DeskModel* desk);

    void onHttpResult(QNetworkReply *reply);
};

#endif // MAINFRAGMENT_H
