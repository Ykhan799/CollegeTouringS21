#include "purchasewindow.h"
#include "ui_purchasewindow.h"

purchasewindow::purchasewindow(QWidget *parent, const QString& campus) :
    QDialog(parent),
    ui(new Ui::purchasewindow)
{ 
    currentCampus = campus;

    vector<QString> souvenirListings;
    QString tempStr;
    QString pricedSouvenir;
    int tempInt = 0;

    ui->setupUi(this);

    // get list of souvenirs at this campus
    souvenirs = database->getSouvenirNamesByCampus(campus);

    // append price listings to all souvenir options in the souvenirs vector
    for(auto it = souvenirs.begin(); it != souvenirs.end(); it++)
    {
        tempStr = QString::number( database->getSouvenirPrice(*it, campus), 'f', 2 );
        pricedSouvenir = souvenirs[tempInt];
        pricedSouvenir.append(" - $");
        pricedSouvenir.append(tempStr);
        souvenirListings.push_back(pricedSouvenir);
        tempInt++;
    }

    // populate souvenirs combo box
    for(auto &i : souvenirListings)
    {
        ui->souvenirList->addItem(i);
    }
}

purchasewindow::~purchasewindow()
{
    delete ui;
}

void purchasewindow::on_purchaseButton_clicked()
{
    Purchase newPurchase;     // Purchase object for current purchase
    QString purchaseTotalStr; // used to display how much was spent in a purchase
    int purchaseCount;        // used to retrieve the number of items purchased

    purchaseCount = ui->purchaseEntry->value();

    if (purchaseCount > 0)
    {
        // set up new Purchase object
        newPurchase.campusName = currentCampus;
        newPurchase.souvenirName = souvenirs[ ui->souvenirList->currentIndex() ];
        newPurchase.numberPurchased = purchaseCount;
        newPurchase.price = database->getSouvenirPrice(newPurchase.souvenirName, newPurchase.campusName);
        newPurchase.totalSpent = newPurchase.price * newPurchase.numberPurchased;

        // add Purchase object to the purchases vector
        purchases.push_back(newPurchase);

        // string to display on purchase success notification
        purchaseTotalStr = "Total cost for purchase: $";
        purchaseTotalStr.append( QString::number(newPurchase.totalSpent, 'f', 2) );

        // purchase success notification
        QMessageBox::information(this, "Purchase Successful!", purchaseTotalStr);
    }

    ui->purchaseEntry->setValue(1);
}

void purchasewindow::on_doneButton_clicked()
{
    close();
}
