#ifndef PURCHASEMUE_H
#define PURCHASEMUE_H

#include "clientmodel.h"
#include "main.h"
#ifdef ENABLE_WALLET
#include "wallet.h"
#endif

#include <QWidget>
#include <QtNetwork/QtNetwork>

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

private slots:
    void on_currentExchangeRateBox_valueChanged(double value);
    void on_purchAmountBox_valueChanged(double value);
    void on_submitButton_clicked();
    void getTicker();
    void handleGetTicker();
    void handlePurchase();
    void onError(QNetworkReply *reply);

private:
    Ui::PurchaseMue *ui;
    ClientModel *model;
    QNetworkAccessManager *networkAccessManager;
    QTimer *timer;

};

#endif // PURCHASEMUE_H
