#include "purchasemue.h"
#include "ui_purchasemue.h"
#include <qrencode.h>
#include "main.h"
#ifdef ENABLE_WALLET
#include "wallet.h"
#endif
#include "clientmodel.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

PurchaseMue::PurchaseMue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PurchaseMue)
{
    ui->setupUi(this);
    this->networkAccessManager = new QNetworkAccessManager(this);
    getTicker();
    this->timer = new QTimer(this);
    connect(this->timer, SIGNAL(timeout()), this, SLOT(getTicker()));
    this->timer->start(90000);
}
void PurchaseMue::setModel(ClientModel *model)
{
    this->model = model;
}
PurchaseMue::~PurchaseMue()
{
    delete ui;
    delete networkAccessManager;
}

void PurchaseMue::on_submitButton_clicked()
{
    ui->msglabel->setText("");
    QUrl req("https://exchange.muewallet.com/api/v1/purchase");
    QString valueAsString = QString::number(ui->purchAmountBox->value(), 'f', 8);
    req.setQuery("mue_address=" + ui->AddressBox->text() + "&purchase_amount=" + valueAsString);

    QNetworkRequest request(req);
    request.setRawHeader("User-Agent", "PurchaseMue-Qt");
    QNetworkReply *reply = this->networkAccessManager->get(request);
    if (reply->error() != QNetworkReply::NoError) {
        onError(reply);
        return;
    }
    connect(reply, SIGNAL(finished()), this, SLOT(handlePurchase()));
}

void PurchaseMue::on_currentExchangeRateBox_valueChanged(double value)
{
    ui->estimTotalBox->setValue(double(value * ui->purchAmountBox->value()));
}

void PurchaseMue::on_purchAmountBox_valueChanged(double value)
{
    ui->estimTotalBox->setValue(double(value * ui->currentExchangeRateBox->value()));
}

void PurchaseMue::getTicker()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://exchange.muewallet.com/api/v1/current"));
    request.setRawHeader("User-Agent", "PurchaseMue-Qt");
    QNetworkReply *reply = this->networkAccessManager->get(request);
    if (reply->error() != QNetworkReply::NoError) {
        onError(reply);
        return;
    }
    connect(reply, SIGNAL(finished()), this, SLOT(handleGetTicker()));
}


void PurchaseMue::handleGetTicker()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() != QNetworkReply::NoError) {
        onError(reply);
        return;
    }
    if(reply->hasRawHeader("Location")){
        QString strLocation = reply->header(QNetworkRequest::LocationHeader).toString();
        qDebug() << strLocation;
        return;
    }
    QByteArray strHttpData;
    strHttpData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strHttpData);
    if(jsonDoc.isNull() ||!jsonDoc.isObject())
    {//  null or not object format
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    double last = jsonObj.value("result").toObject().value("rate").toDouble();
    //qDebug() << last;
    ui->currentExchangeRateBox->setValue(double(last));
}

void PurchaseMue::handlePurchase()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    if (reply->error() != QNetworkReply::NoError) {
        onError(reply);
    }
    QByteArray strHttpData;
    strHttpData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strHttpData);
    if(jsonDoc.isNull() ||!jsonDoc.isObject())
    {
        qDebug() << "null or not object format";
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
    if(jsonObj.contains("error"))
    {
        QString msg = jsonObj.value("error").toString();
        qDebug() << msg;
        ui->msglabel->setText(msg);
        return;
    }
    QString BitcoinURI = jsonObj.value("BitcoinURI").toString();
    QString btc_address = jsonObj.value("invoice").toObject().value("btc_address").toString();
    int invoice_id = jsonObj.value("invoice").toObject().value("invoice_id").toInt();
    double price_in_btc = jsonObj.value("invoice").toObject().value("price_in_btc").toDouble();

    QString uri = BitcoinURI;
    ui->lblQRCode->setText("");



    if(!uri.isEmpty())
    {
            ui->amountLabel->setText("Amount:");
            ui->amount->setText(QString::number((double)price_in_btc, 'f', 8));

            ui->invoiceLabel->setText("Invoice ID:");
            ui->invoice_id->setText("<a href=\"https://exchange.muewallet.com/status/" + QString::number((int)invoice_id) + "\">" + QString::number((int)invoice_id) + "</a>");

            ui->btc_address->setText("<a href=\""+uri+"\">" + btc_address + "</a>");

            QRcode *code = QRcode_encodeString(uri.toUtf8().constData(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
            if (!code)
            {
                ui->lblQRCode->setText(tr("Error encoding URI into QR Code."));
                return;
            }
            QImage myImage = QImage(code->width + 8, code->width + 8, QImage::Format_RGB32);
            myImage.fill(0xeeeeee);
            unsigned char *p = code->data;
            for (int y = 0; y < code->width; y++)
            {
                for (int x = 0; x < code->width; x++)
                {
                    myImage.setPixel(x + 4, y + 4, ((*p & 1) ? 0x0 : 0xeeeeee));
                    p++;
                }
            }
            QRcode_free(code);

            ui->lblQRCode->setPixmap(QPixmap::fromImage(myImage).scaled(200, 200));
    }
}

void PurchaseMue::onError(QNetworkReply *reply)
{
    qDebug() << reply->errorString();
    //emit error(reply->errorString());
    reply->deleteLater();
}
