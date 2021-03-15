#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include <common/base/basescreensfactory.h>


namespace screens {
    static const QString SERVER_URL = "http://jutter.online/mytask";
    //static const QString SERVER_URL = "http://localhost:8080";

    static const QString SPLASH_TAG = "splash";
    static const QString START_TAG = "start";
    static const QString LOGIN_TAG = "login";
    static const QString REGISTRATION_TAG = "registration";
    static const QString MAIN_TAG = "main";
    static const QString ADD_DESK_TAG = "add_desk";
    static const QString DESK_TAG = "desk_detail";
    static const QString ADD_CARD_TAG = "add_card";
    static const QString USERS_TAG = "users_list";
    static const QString CREATE_INVITE_TAG = "create_invite";
    static const QString INVITE_LIST_TAG = "invite_list";

};

class ScreensFactory: public BaseScreensFactory {
public:
    ScreensFactory();
    ~ScreensFactory();

    BaseFragment* create(QString tag) override;
    QString createStart() override;
};

#endif // SCREENSFACTORY_H
