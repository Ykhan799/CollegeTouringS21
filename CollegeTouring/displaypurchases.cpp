#include "displaypurchases.h"
#include "ui_displaypurchases.h"

displaypurchases::displaypurchases(QWidget *parent, vector<Purchase>* purchaseList) :
    QDialog(parent),
    ui(new Ui::displaypurchases)
{
    allPurchases = *purchaseList;
    double grandTotal = 0;

    if (!allPurchases.empty())
    {
        for (auto it = allPurchases.begin(); it != allPurchases.end(); it++)
        {
            grandTotal += it->totalSpent;
        }
    }

    ui->totalLabel->setText(QString::number(grandTotal));

    ui->setupUi(this);

}

displaypurchases::~displaypurchases()
{
    delete ui;
}

void displaypurchases::on_closeButton_clicked()
{
    close();
}
