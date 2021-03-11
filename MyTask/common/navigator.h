#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <common/base/basefragment.h>
#include <common/base/basescreensfactory.h>

#include <QStackedWidget>


/**
 * @brief The Navigator class
 *
 * Навигация в риложении и логика замены экранов.
 *
 * <p>Экраны лежат в списке и мы можем выполнить
 * переход дальше по цепочке, заменить текущий экран
 * или перейти назад по цепочке.</p>
 *
 * @author Solyanoy Leonid (solyanoy.leonid@gmail.com)
 */
class Navigator {

private:
    QStackedWidget *currentContainer;
    BaseScreensFactory *screensFactory;
    QLinkedList<BaseFragment *> *screenStack;

public:
    const QString SPLASH_TAG = "splash_tag";
    const QString START_TAG = "start_tag";

    Navigator(
            QStackedWidget *container,
            BaseScreensFactory *screensFactory
    );
    ~Navigator();

    /**
     * @brief navigateTo
     * @param tag имя следующего экрана.
     *
     * Переход к следующему экрану.
     */
    void navigateTo(QString tag);

    /**
     * @brief back
     *
     * Переход назад по цепочке.
     */
    void back();

    /**
     * @brief replace
     * @param tag имя экрана на который
     *        произойдет замена.
     *
     * Замена текущего экрана с сохранением
     * предыдущей цепочки.
     */
    void replace(QString tag);
};

#endif // NAVIGATOR_H
