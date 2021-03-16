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

    // assign prices to all souvenirs in the list
    for(auto it = souvenirs.begin(); it != souvenirs.end(); it++)
    {
        tempStr = QString::number( database->getSouvenirPrice(*it, campus) );
        pricedSouvenir = souvenirs[tempInt];
        pricedSouvenir.append(" - $");
        pricedSouvenir.append(tempStr);
        qDebug() << "pricedSouvenir " << pricedSouvenir;
        souvenirListings.push_back(pricedSouvenir);
        tempInt++;
    }

   // populate souvenirs combo box
    for(auto &i : souvenirListings) {
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
    Purchase newPurchase;                                 // Purchase object for current purchase
    bool invalid = false;                                 // whether the input is invalid for # souvenirs to purchase
    QString purchaseCountStr = ui->purchaseEntry->text(); // user input for # of souvenirs to purchase
    int purchaseCount = purchaseCountStr.toInt();         // conversion of input for # of souvenirs

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

        // purchase success notification
        QMessageBox::information(this, "Success!", "Purchase was successful.");

        ui->purchaseEntry->setText("");
    }
}

void purchasewindow::on_doneButton_clicked()
{
    close();
}
