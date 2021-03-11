#include "navigator.h"

Navigator::Navigator(
        QStackedWidget *container,
        BaseScreensFactory *screensFactory
) {
    this->screensFactory = screensFactory;
    this->currentContainer = container;
}

Navigator::~Navigator() {
    delete screensFactory;
}

void Navigator::navigateTo(QString tag) {

}

void Navigator::back() {

}

void Navigator::replace(QString tag) {

}
