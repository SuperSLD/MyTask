#ifndef DESKWIDGET_H
#define DESKWIDGET_H

#include <QFrame>
#include <QWidget>

#include <models/deskmodel.h>

class DeskWidget: public QFrame {
    Q_OBJECT
public:
    DeskWidget(DeskModel desk);
};

#endif // DESKWIDGET_H
