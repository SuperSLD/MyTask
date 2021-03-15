#ifndef ADDCARDFRAGMENT_H
#define ADDCARDFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QPushButton>

#include <models/deskmodel.h>

class AddCardFragment: public BaseFragment {
    Q_OBJECT
private:
    QString token;

    DeskModel *model;

    QLineEdit *titleEdit;
    QPlainTextEdit *descriptionEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManager;

public:
    AddCardFragment();
    ~AddCardFragment();

    void setData(BaseModel* model) override;
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

#endif // ADDCARDFRAGMENT_H
