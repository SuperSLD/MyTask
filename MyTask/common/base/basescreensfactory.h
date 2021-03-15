#ifndef BASESCREENSFACTORY_H
#define BASESCREENSFACTORY_H

#include "basefragment.h"

#include <QString>


/**
 * @brief The BaseScreensFactory class
 *
 * Абстрактная фабрика экранов.
 */
class BaseScreensFactory {
public:
    BaseScreensFactory();
    ~BaseScreensFactory();

    /**
     * @brief create
     * @param tag идентификатор экрана.
     *
     * Создание экрана по его
     * идентификатору для навигатора.
     * (фабрика инициализируетя при создании навигатора)
     *
     * @return BaseFragmnt.
     */
    virtual BaseFragment* create(QString tag);

    /**
     * @brief createStart
     *
     * Создание стартового окна прпиложения
     * для навигатора.
     *
     * @return стартовое окно приложения.
     */
    virtual QString createStart();

    //MainWindow *window;
};

#endif // BASESCREENSFACTORY_H
