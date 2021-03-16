#include "purchasewindow.h"
#include "ui_purchasewindow.h"

purchasewindow::purchasewindow(QWidget *parent, const QString& campus) :
    QDialog(parent),
    ui(new Ui::purchasewindow)
{
    vector<QString> souvenirs; // list of souvenirs available at this campus
//    vector<QString> souvenirListings;
//    QString tempStr;
//    QString pricedSouvenir;

//    //getSouvenirPrice(const QString& souvenir, const QString& campus)

//    //QString startDist = QString::fromStdString(startingDist);

//    // ui->distanceVarLabel->setText(QString::number(totalDistance));

    ui->setupUi(this);

//    for(int j = 0; j < souvenirs.size(); j++)
//    {
//        tempStr = QString::number( database->getSouvenirPrice(souvenirs[j], campus) );
//        pricedSouvenir = souvenirs[j];
//        pricedSouvenir.append(" - $");
//        pricedSouvenir.append(tempStr);
//        souvenirListings.push_back(pricedSouvenir);
//    }

//    // get list of souvenirs at this campus
    souvenirs = database->getSouvenirNamesByCampus(campus);


   // populate souvenirs combo box
    for(auto &i : souvenirs) {
        ui->souvenirList->addItem(i);
    }


}

purchasewindow::~purchasewindow()
{
    delete ui;
}

void purchasewindow::on_cancelButton_clicked()
{
    close();
}

void purchasewindow::on_purchaseButton_clicked()
{
    // purchase current item

}

void purchasewindow::on_doneButton_clicked()
{
    // close this window and complete purchase
}
