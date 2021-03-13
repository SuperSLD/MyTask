#include "screensfactory.h"

#include <ui/mainfragment.h>
#include <ui/splashfragment.h>

#include <ui/auth/loginfragment.h>
#include <ui/auth/registrationfragment.h>
#include <ui/auth/startfragment.h>

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
    } else {
        return nullptr;
    }
}
