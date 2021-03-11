#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include <QWidget>

class BaseFragment: public QWidget{
    Q_OBJECT

protected:
    //Navigator *navigator;

public:
    BaseFragment();
    ~BaseFragment();
};

#endif // BASEFRAGMENT_H
