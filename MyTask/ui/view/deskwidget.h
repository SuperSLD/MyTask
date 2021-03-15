#ifndef DESKWIDGET_H
#define DESKWIDGET_H

#include <QFrame>
#include <QPushButton>
#include <QWidget>

#include <models/deskmodel.h>

/**
 * @brief The DeskWidget class
 *
 * Отображение доски на главном экране.
 */
class DeskWidget: public QFrame {
    Q_OBJECT

private:
    DeskModel *model;
public:
    DeskWidget(DeskModel *desk);
    ~DeskWidget();

signals:
    /**
     * @brief deskSelected
     * @param desk доска прикрепленная к
     *        этому виджету.
     *
     * Вызывается при нажатии на кнопку "открыть".
     */
    void deskSelected(DeskModel* desk);

public slots:
    void buttonPressed();
};

#endif // DESKWIDGET_H
