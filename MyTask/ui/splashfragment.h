#ifndef SPLASHFRAGMENT_H
#define SPLASHFRAGMENT_H

#include <common/base/basefragment.h>



class SplashFragment: public BaseFragment {
    Q_OBJECT

public:
    SplashFragment();
    ~SplashFragment();
public slots:
    /**
     * @brief openStartScreen
     *
     * Проверяем сохранен ли токен
     * и переходим либо к стартовому экрану
     * либо к главному.
     */
    void openStartScreen();
};

#endif // SPLASHFRAGMENT_H
