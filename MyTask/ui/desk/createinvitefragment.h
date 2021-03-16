#ifndef CREATEINVITEFRAGMENT_H
#define CREATEINVITEFRAGMENT_H

#include <common/base/basefragment.h>

#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QPushButton>

#include <models/deskmodel.h>



class CreateInviteFragment: public BaseFragment {
    Q_OBJECT
private:
    QString token;

    DeskModel *model;

    QLineEdit *titleEdit;
    QPushButton *createButton;
    QNetworkAccessManager *networkManager;
public:
    CreateInviteFragment();
    ~CreateInviteFragment();

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

#endif // CREATEINVITEFRAGMENT_H
