#ifndef PURCHASEMUE_H
#define PURCHASEMUE_H

#include "clientmodel.h"
#include "main.h"
#ifdef ENABLE_WALLET
#include "wallet.h"
#endif

#include <QWidget>
#include <QWebView>

namespace Ui {
class PurchaseMue;
}
class ClientModel;

class PurchaseMue : public QWidget
{
    Q_OBJECT

public:
    explicit PurchaseMue(QWidget *parent = 0);
    ~PurchaseMue();

    void setModel(ClientModel *model);

public slots:

private slots:

private:
    Ui::PurchaseMue *ui;
    ClientModel *model;

};

#endif // PURCHASEMUE_H
