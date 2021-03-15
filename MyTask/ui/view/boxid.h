#ifndef BOXID_H
#define BOXID_H

#include <QCheckBox>



class BoxId: public QCheckBox {
    Q_OBJECT
private:
    QString id;
public:
    BoxId(QString id);
public slots:
    void checkClick();
signals:
    void clickCheckbox(QString id);
};

#endif // BOXID_H
