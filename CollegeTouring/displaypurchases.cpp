#include "displaypurchases.h"
#include "ui_displaypurchases.h"

displaypurchases::displaypurchases(QWidget *parent, vector<Purchase>* purchaseList) :
    QDialog(parent),
    ui(new Ui::displaypurchases)
{
    allPurchases = *purchaseList;            // assign allPurchases to vector pointed to by purchaseList
    vector<QString> uniquePurchaseLocations; // vector of unique campuses where purchases were made

    ui->setupUi(this);

    for (auto it = purchaseList->begin(); it != purchaseList->end(); it++)
    {
        // check if the current purchase's campus already exists in uniquePurchaseLocations
        auto foundIt = std::find(uniquePurchaseLocations.begin(), uniquePurchaseLocations.end(), it->campusName);

        // if current purchase's campus does not exist in uniquePurchaseLocations, add it
        if (foundIt == uniquePurchaseLocations.end())
        {
            uniquePurchaseLocations.push_back(it->campusName);
        }
    }

    // populate the group box with all campuses
    ui->campusList->addItem("All Campuses");
    for(auto it = uniquePurchaseLocations.begin(); it != uniquePurchaseLocations.end(); it++)
    {
        ui->campusList->addItem(*it);
    }

    // populate the transaction table with all purchases made during the trip
    populateTransactionTable(purchaseList, "", true);
}

displaypurchases::~displaypurchases()
{
    delete ui;
}

void displaypurchases::populateTransactionTable(vector<Purchase>* purchaseList, const QString& campus, bool displayAll)
{
    vector<Purchase> tempPurchases; // holds purchases that will be displayed on the table
    double grandTotal = 0;          // the grand total for the currently selected campus(es)
    int rowCount = 0;               // the row that is currently having items added to it

    // leave function if no campus was provided
    if (!displayAll && campus == "")
    {
        return;
    }

    // set up the table of transactions
    ui->transactionTableWidget->setColumnCount(5);
    ui->transactionTableWidget->setColumnWidth(0, 275);
    ui->transactionTableWidget->setColumnWidth(1, 225);
    ui->transactionTableWidget->setColumnWidth(2, 70);
    ui->transactionTableWidget->setColumnWidth(3, 70);
    ui->transactionTableWidget->setColumnWidth(4, 108);
    ui->transactionTableWidget->setRowCount(1);
    ui->transactionTableWidget->verticalHeader()->hide();
    ui->transactionTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Campus"));
    ui->transactionTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Souvenir"));
    ui->transactionTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Price"));
    ui->transactionTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Quantity"));
    ui->transactionTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Total"));
    ui->transactionTableWidget->setSortingEnabled(false);

    // save purchases that will be displayed on the table according to the campus name that was provided
    for (auto it = (*purchaseList).begin(); it != (*purchaseList).end(); it++)
    {
        if (displayAll || it->campusName == campus)
        {
            tempPurchases.push_back(*it);
            grandTotal += it->totalSpent;
        }
    }

    // display the grand total spent during the trip at the specified campus(es)
    ui->totalLabel->setText(QString::number(grandTotal));

    // create and insert items into each individual cell of the transaction table
    for (auto it = tempPurchases.begin(); it != tempPurchases.end(); it++)
    {
        rowCount++;
        ui->transactionTableWidget->insertRow(rowCount);

        // populating each column in row at rowCount with correct data
        for (int j = 0; j < 5; j++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();

            // set data for new item according to what column is currently being populated
            switch (j)
            {
            case 0:
                newItem->setText( it->campusName );
                break;
            case 1:
                newItem->setText( it->souvenirName );
                break;
            case 2:
                newItem->setText( QString::number(it->price) );
                break;
            case 3:
                newItem->setText( QString::number(it->numberPurchased) );
                break;
            case 4:
                newItem->setText( QString::number(it->totalSpent) );
                break;
            default:
                break;
            }

            newItem->setTextAlignment(Qt::AlignHCenter);

            // set the item on the table at row rowCount, column j
            ui->transactionTableWidget->setItem(rowCount, j, newItem);
        }
    }
}

void displaypurchases::on_closeButton_clicked()
{
    close();
}

void displaypurchases::on_displayButton_clicked()
{
    bool displayingAll = false;
    vector<Purchase> *vecPtr = &allPurchases;
    QString campusSelection = ui->campusList->currentText();

    if (ui->campusList->currentIndex() == 0)
    {
        displayingAll = true;
    }

    populateTransactionTable(vecPtr, campusSelection, displayingAll);
}
