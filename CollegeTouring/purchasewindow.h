#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QDialog>
#include <vector>
#include "dbmanager.h"
#include "tripRoutePlanner.h"

namespace Ui {
class purchasewindow;
}

class purchasewindow : public QDialog
{
    Q_OBJECT

public:
    explicit purchasewindow(QWidget *parent = nullptr, const QString& campus = "");
    ~purchasewindow();

private slots:
    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

    void on_purchaseButton_clicked();

    void on_doneButton_clicked();

private:
    Ui::purchasewindow *ui;

    DbManager *database;

    //vector<Purchase> purchases;
};

#endif // PURCHASEWINDOW_H
