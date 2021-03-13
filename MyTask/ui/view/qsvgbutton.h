#ifndef QSVGBUTTON_H
#define QSVGBUTTON_H

#include <QPushButton>
#include <QString>


/**
 * @brief The QSvgButton class
 *
 * Кнопка с cvg иконкой.
 * Удивительно что в Qt нет своей такой.
 */
class QSvgButton: public QPushButton {
    Q_OBJECT

public:
    QSvgButton(QString path, QSize size);
    ~QSvgButton();
};

#endif // QSVGBUTTON_H
