#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include <common/base/basescreensfactory.h>



class ScreensFactory: public BaseScreensFactory {
public:
    const QString SPLASH_TAG = "splash";
    const QString START_TAG = "start";
    const QString LOGIN_TAG = "login";

    ScreensFactory();
    ~ScreensFactory();

    BaseFragment * create(QString tag);
};

#endif // SCREENSFACTORY_H
