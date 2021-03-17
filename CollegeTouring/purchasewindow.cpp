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
        tempStr = QString::number( database->getSouvenirPrice(*it, campus) );
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
    Purchase newPurchase;                                 // Purchase object for current purchase
    QString purchaseCountStr = ui->purchaseEntry->text(); // user input for # of souvenirs to purchase
    QString purchaseTotalStr;                             // used to display how much was spent in a purchase
    int purchaseCount = purchaseCountStr.toInt();         // conversion of input for # of souvenirs
    bool invalid = false;                                 // whether the input is invalid for # souvenirs to purchase

    // check for letters in string
    for (int i = 0; i < purchaseCountStr.size(); i++)
    {
        if (purchaseCountStr[i].isLetter())
        {
            // invalid set to true and break if letter is found
            invalid = true;
            break;
        }
    }

    // invalid input
    if (invalid || purchaseCountStr == "" || purchaseCount < 0 )
    {
        QMessageBox::information(this, "Error", "Please enter a valid number.");
        ui->purchaseEntry->setText("");
    }
    else
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
        purchaseTotalStr.append( QString::number(newPurchase.totalSpent) );

        // purchase success notification
        QMessageBox::information(this, "Purchase Successful!", purchaseTotalStr);

        ui->purchaseEntry->setText("");
    }
}

void purchasewindow::on_doneButton_clicked()
{
    close();
}
