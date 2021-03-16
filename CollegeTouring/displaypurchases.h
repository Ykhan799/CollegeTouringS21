#ifndef DISPLAYPURCHASES_H
#define DISPLAYPURCHASES_H

#include <QDialog>
#include <vector>
#include "purchasewindow.h"

namespace Ui {
class displaypurchases;
}

class displaypurchases : public QDialog
{
    Q_OBJECT

public:
    explicit displaypurchases(QWidget *parent = nullptr, vector<Purchase>* purchaseList = nullptr);

    ~displaypurchases();

private slots:
    void on_closeButton_clicked();

private:
    Ui::displaypurchases *ui;

    vector<Purchase> allPurchases;
};

#endif // DISPLAYPURCHASES_H
