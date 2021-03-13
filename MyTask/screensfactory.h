#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include <common/base/basescreensfactory.h>


namespace screens {
    static const QString SERVER_URL = "https://jutter.online/mytask";

    static const QString SPLASH_TAG = "splash";
    static const QString START_TAG = "start";
    static const QString LOGIN_TAG = "login";
    static const QString REGISTRATION_TAG = "registration";
    static const QString MAIN_TAG = "main";
};

class ScreensFactory: public BaseScreensFactory {
public:
    ScreensFactory();
    ~ScreensFactory();

    BaseFragment* create(QString tag) override;
};

#endif // SCREENSFACTORY_H
