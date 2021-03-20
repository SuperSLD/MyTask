#include "screensfactory.h"

#include <ui/mainfragment.h>
#include <ui/splashfragment.h>

#include <ui/auth/loginfragment.h>
#include <ui/auth/registrationfragment.h>
#include <ui/auth/startfragment.h>

#include <ui/desk/addcardfragment.h>
#include <ui/desk/adddeskfragment.h>
#include <ui/desk/createinvitefragment.h>
#include <ui/desk/deskfragment.h>
#include <ui/desk/historyfragment.h>
#include <ui/desk/userslistfragment.h>

#include <ui/invite/invitelistfragment.h>

using namespace screens;

ScreensFactory::ScreensFactory() {

}

ScreensFactory::~ScreensFactory() {

}

BaseFragment* ScreensFactory::create(QString tag) {
    qDebug("ScreensFactory create");
    if (tag == SPLASH_TAG) {
        return new SplashFragment;
    } else if (tag == START_TAG) {
        return new StartFragment;
    } else if (tag == LOGIN_TAG) {
        return new LoginFragment;
    } else if (tag == REGISTRATION_TAG) {
        return new RegistrationFragment;
    } else if (tag == MAIN_TAG) {
        return new MainFragment;
    } else if (tag == ADD_DESK_TAG) {
        return new AddDeskFragment;
    } else if (tag == DESK_TAG) {
        return new DeskFragment;
    } else if (tag == ADD_CARD_TAG) {
        return new AddCardFragment;
    } else if (tag == USERS_TAG) {
        return new UsersListFragment;
    } else if (tag == CREATE_INVITE_TAG) {
        return new CreateInviteFragment;
    } else if (tag == INVITE_LIST_TAG) {
        return new InviteListFragment;
    } else if (tag == HISTORY_DESK_TAG) {
        return new HistoryFragment;
    } else {
        return nullptr;
    }
}

QString ScreensFactory::createStart() {
    return SPLASH_TAG;
}


