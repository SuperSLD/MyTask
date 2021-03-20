#ifndef HSITORYFRAGMENT_H
#define HSITORYFRAGMENT_H

#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <common/base/basefragment.h>
#include <models/deskmodel.h>
#include <models/historymodel.h>
#include <ui/view/loadingwidget.h>

class HistoryFragment: public BaseFragment {
    Q_OBJECT
private:
    QNetworkAccessManager *networkManager;
    QString token;

    QList<HistoryModel> historyList;
    DeskModel *model;

    LoadingWidget *loading;
    QVBoxLayout *start;

    void loadData();
    void parseHistoryList(QJsonArray items);
public:
    HistoryFragment();
    ~HistoryFragment();

    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();

    void onHttpResult(QNetworkReply *reply);
};

#endif // HSITORYFRAGMENT_H
