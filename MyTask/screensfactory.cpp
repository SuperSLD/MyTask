#include "screensfactory.h"

ScreensFactory::ScreensFactory() {

}

ScreensFactory::~ScreensFactory() {

}

BaseFragment* ScreensFactory::create(QString tag) {
    if (tag == SPLASH_TAG) {
        return
    } else {
        return nullptr;
    }
}
