#include "deskwidget.h"

#include <models/deskmodel.h>

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

#include <style/stylecontainer.h>
using namespace styles;

DeskWidget::DeskWidget(DeskModel desk) {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QLabel *title = new QLabel(desk.title);

    mainLayout->addWidget(title);
    this->setLayout(mainLayout);
    this->setMaximumWidth(396);
    this->setMinimumWidth(396);
    this->setObjectName("desk");
    this->setStyleSheet(DESK_WIDGET);
}
