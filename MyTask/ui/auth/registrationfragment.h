#ifndef REGISTRATIONFRAGMENT_H
#define REGISTRATIONFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>

#include <ui/view/waitingspinnerwidget.h>



class RegistrationFragment : public BaseFragment {
    Q_OBJECT
private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QNetworkAccessManager *networkManager;
    QPushButton *loginButton;

    WaitingSpinnerWidget *loading;
    QFrame *loadingContaiter;
public:
    RegistrationFragment();
    ~RegistrationFragment();
public slots:
    void onBackPressed();
    void onRegPressed();
    void onRegResult(QNetworkReply *reply);

    void checkData();
};

#endif // REGISTRATIONFRAGMENT_H
