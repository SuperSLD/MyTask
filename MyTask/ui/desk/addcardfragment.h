#ifndef ADDCARDFRAGMENT_H
#define ADDCARDFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStackedWidget>

#include <models/deskmodel.h>

#include <ui/view/qsvgbutton.h>
#include <ui/view/waitingspinnerwidget.h>

class AddCardFragment: public BaseFragment {
    Q_OBJECT
private:
    QString token;

    DeskModel *model;
    QString currentType = "simple";

    QLineEdit *titleEdit;
    QLineEdit *cardTitleEdit;

    WaitingSpinnerWidget *loading;
    WaitingSpinnerWidget *loadingBox;

    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QPushButton *createBoxButton;

    QSvgButton *addBoxTitleButton;

    QVBoxLayout *titleWidgetList;
    QList<QString> titleList;

    QPushButton *simpleButtom;
    QPushButton *boxButton;
    QStackedWidget *stack;

    QNetworkAccessManager *networkManager;

public:
    AddCardFragment();
    ~AddCardFragment();

    void setData(BaseModel* model) override;
public slots:
    void onBackPressed();
    void onCreatePressed();
    void onHttpResult(QNetworkReply *reply);
    void onBoxTitleAdd();

    void onText();
    void onBox();

    /**
     * @brief checkData
     *
     * проверка введенных данных
     * на корректность.
     */
    void checkData();
    void checkBoxTitle();
};

#endif // ADDCARDFRAGMENT_H
