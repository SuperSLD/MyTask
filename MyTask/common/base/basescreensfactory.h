#ifndef BASESCREENSFACTORY_H
#define BASESCREENSFACTORY_H

#include "basefragment.h"

#include <QString>



class BaseScreensFactory {
public:
    BaseScreensFactory();
    ~BaseScreensFactory();

    BaseFragment* create(QString tag);
};

#endif // BASESCREENSFACTORY_H
