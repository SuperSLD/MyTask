#include "loadingwidget.h"

#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

LoadingWidget::LoadingWidget() {
    QVBoxLayout *container = new QVBoxLayout;
    QLabel *lbl = new QLabel;
    QMovie *movie = new QMovie(":/resc/resc/loader.gif");

    lbl->setMovie(movie);
    lbl->setMinimumSize(QSize(150,150));
    lbl->setMaximumSize(QSize(150,150));
    lbl->setStyleSheet("background: #000000;");
    movie->start();

    container->addWidget(lbl);
    this->setLayout(container);
}
