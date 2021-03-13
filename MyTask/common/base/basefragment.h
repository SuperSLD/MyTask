#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include <QFrame>
#include <QWidget>

class BaseFragment: public QFrame {
    Q_OBJECT

signals:
    void back();
    void navigateTo(QString tag);
    void newRootScreen(QString tag);
    void replace(QString tag);

public:
    BaseFragment();
    ~BaseFragment();
};

#endif // BASEFRAGMENT_H
