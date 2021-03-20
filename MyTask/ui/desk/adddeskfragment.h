#ifndef ADDDESKFRAGMENT_H
#define ADDDESKFRAGMENT_H

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QWidget>
#include <QNetworkReply>
#include <QPlainTextEdit>

#include <common/base/basefragment.h>

#include <ui/view/waitingspinnerwidget.h>

class AddDeskFragment : public BaseFragment{
    Q_OBJECT

private:
    QString token;

    WaitingSpinnerWidget *loading;

    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManager;

public:
    AddDeskFragment();
    ~AddDeskFragment();

public slots:
    void onBackPressed();
    void onCreatePressed();
    void onHttpResult(QNetworkReply *reply);

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
};

#endif // ADDDESKFRAGMENT_H
