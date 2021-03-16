#ifndef INVITEWIDGET_H
#define INVITEWIDGET_H

#include <QFrame>

#include <models/deskmodel.h>



class InviteWidget: public QFrame {
    Q_OBJECT

private:
    DeskModel *model;

    /**
     * @brief id идентификатор приглашения
     * который необходимо прправить для
     * ответа на приглашение.
     */
    QString id;
public:
    InviteWidget(DeskModel *desk, QString id);
    ~InviteWidget();

signals:
    /**
     * @brief deskSelected
     * @param desk доска прикрепленная к
     *        этому виджету.
     *
     * Вызывается при нажатии на кнопку "открыть".
     */
    void deskAccept(QString id);

    void deskCancel(QString id);

public slots:
    void buttonCancel();
    void buttonAccept();
};

#endif // DESKWIDGET_H
