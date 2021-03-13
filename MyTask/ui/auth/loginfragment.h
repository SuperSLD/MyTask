#ifndef LOGINFRAGMENT_H
#define LOGINFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>



class LoginFragment: public BaseFragment {
    Q_OBJECT
private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QNetworkAccessManager *networkManager;
public:
    LoginFragment();
    ~LoginFragment();
public slots:
    void onBackPressed();
    void onLoginPressed();
    void onHttpResult(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};

#endif // LOGINFRAGMENT_H
