#ifndef REGISTRATIONFRAGMENT_H
#define REGISTRATIONFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>



class RegistrationFragment : public BaseFragment {
    Q_OBJECT
private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QNetworkAccessManager *networkManager;
public:
    RegistrationFragment();
    ~RegistrationFragment();
public slots:
    void onBackPressed();
    void onRegPressed();
    void onRegResult(QNetworkReply *reply);
};

#endif // REGISTRATIONFRAGMENT_H
