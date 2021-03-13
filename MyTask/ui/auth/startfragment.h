#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include <common/base/basefragment.h>



class StartFragment: public BaseFragment {
    Q_OBJECT
public:
    StartFragment();
    ~StartFragment();

public slots:
    void openLogin();
    void openRegistration();
};

#endif // STARTFRAGMENT_H
