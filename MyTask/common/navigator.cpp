#include "navigator.h"
#include "screensfactory.h"

#include <QLinkedList>

using namespace screens;

Navigator::Navigator(
        QStackedWidget *container,
        BaseScreensFactory *screensFactory
) {
    qDebug("create navigator");
    this->screensFactory = screensFactory;
    this->currentContainer = container;
    qDebug("create start fragment");
    BaseFragment* startFragment = getStartScreen();
    qDebug("append start fragment");
    this->stack.append(startFragment);

    qDebug("add widget");
    currentContainer->addWidget(stack.last());
    currentContainer->setCurrentIndex(0);
}

Navigator::~Navigator() {
}

void Navigator::navigateTo(QString tag) {
    qDebug("Navigator navigateTo");
    BaseFragment *newFragment = this->screensFactory->create(tag);
    disconnectFragment(stack.last());
    connectFragment(newFragment);
    stack.append(newFragment);
    currentContainer->addWidget(newFragment);
    currentContainer->setCurrentWidget(newFragment);
}

void Navigator::back() {
    qDebug("Navigator back");
    currentContainer->removeWidget(stack.last());
    delete stack.last();
    stack.removeLast();
    connectFragment(stack.last());
    currentContainer->setCurrentWidget(stack.last());
}

void Navigator::replace(QString tag) {
    qDebug("Navigator replace");
    BaseFragment *newFragment = this->screensFactory->create(tag);
    currentContainer->removeWidget(stack.last());
    delete stack.last();
    stack.removeLast();
    connectFragment(newFragment);
    currentContainer->addWidget(newFragment);
}

void Navigator::newRootScreen(QString tag) {
    qDebug("Navigator newRootScreen");
    BaseFragment *newFragment = this->screensFactory->create(tag);
    disconnectFragment(stack.last());
    stack.clear();
    connectFragment(newFragment);
    for(int i = currentContainer->count(); i >= 0; i--)
    {
        QWidget* widget = currentContainer->widget(i);
        currentContainer->removeWidget(widget);
        widget->deleteLater();
    }
    currentContainer->addWidget(newFragment);
    stack.append(newFragment);
}

BaseFragment* Navigator::getStartScreen() {
    return createAndConnect(SPLASH_TAG);
}

void Navigator::connectFragment(BaseFragment *fragment) {
    qDebug("Navigator connect slots");
    connect(fragment, &BaseFragment::back, this, &Navigator::back);
    connect(fragment, &BaseFragment::replace, this, &Navigator::replace);
    connect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
    connect(fragment, &BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
}

void Navigator::disconnectFragment(BaseFragment *fragment) {
    qDebug("Navigator disconnect slots");
    disconnect(fragment, &BaseFragment::back, this, &Navigator::back);
    disconnect(fragment, &BaseFragment::replace, this, &Navigator::replace);
    disconnect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
    disconnect(fragment, &BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
}

BaseFragment* Navigator::createAndConnect(QString tag) {
    BaseFragment *fragment = this->screensFactory->create(tag);
    qDebug("Navigator create screen");
    connectFragment(fragment);
    return fragment;
}
