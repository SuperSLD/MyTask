#include "linewidget.h"
#include "style/stylecontainer.h"
using namespace styles;

LineWidget::LineWidget() {
    this->setMaximumHeight(4);
    this->setMinimumHeight(4);
    this->setStyleSheet("background: "+COLOR_BORDER+";");
}
