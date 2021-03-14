#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include <common/base/basefragment.h>

#include <QNetworkAccessManager>


class MainFragment: public BaseFragment {
    Q_OBJECT
private:
    QNetworkAccessManager *networkManager;

public:
    MainFragment();
    ~MainFragment();
};

#endif // MAINFRAGMENT_H
