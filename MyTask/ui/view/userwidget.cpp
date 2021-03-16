#include "userwidget.h"

#include <models/usermodel.h>
#include <QLabel>
#include <QSvgWidget>
#include <QVBoxLayout>

#include <style/stylecontainer.h>
using namespace styles;

UserWidget::UserWidget(UserModel *user) {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QSvgWidget *profileImage = new QSvgWidget(":/resc/resc/user_circle.svg");
    QLabel *title = new QLabel("@" + user->name);
    QHBoxLayout *fuckContainer = new QHBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(TITLE_LABLE);
    title->setContentsMargins(24,24,24,24);
    title->setWordWrap(true);
    title->setMaximumWidth(325);

    profileImage->setMaximumSize(QSize(100,100));
    profileImage->setContentsMargins(0,35,0,0);
    profileImage->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    fuckContainer->addWidget(profileImage);

    mainLayout->addLayout(fuckContainer);
    mainLayout->addWidget(title);

    this->setLayout(mainLayout);
    this->setObjectName("desk");
    this->setMinimumHeight(mainLayout->geometry().height());
    this->setStyleSheet(DESK_WIDGET);
}
