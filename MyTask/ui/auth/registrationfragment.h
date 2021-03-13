#ifndef REGISTRATIONFRAGMENT_H
#define REGISTRATIONFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>



class RegistrationFragment : public BaseFragment {
    Q_OBJECT
private:
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
public:
    RegistrationFragment();
    ~RegistrationFragment();
public slots:
    void onBackPressed();
};

#endif // REGISTRATIONFRAGMENT_H
