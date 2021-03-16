#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QDialog>
#include <vector>
#include <QMessageBox>
#include "dbmanager.h"

struct Purchase
{
    QString campusName;
    QString souvenirName;
    int numberPurchased;
    double price;
    double totalSpent;
};

namespace Ui {
class purchasewindow;
}

class purchasewindow : public QDialog
{
    Q_OBJECT

public:
    explicit purchasewindow(QWidget *parent = nullptr, const QString& campus = "");
    ~purchasewindow();

    vector<Purchase> purchases;

private slots:
    void on_cancelButton_clicked();

    void on_purchaseButton_clicked();

    void on_doneButton_clicked();

private:
    Ui::purchasewindow *ui;

    DbManager *database;

    QString currentCampus;

    vector<QString> souvenirs;
};

#endif // PURCHASEWINDOW_H
