#ifndef DISPLAYPURCHASES_H
#define DISPLAYPURCHASES_H

#include <QDialog>
#include <QTableWidget>
#include <vector>
#include "purchasewindow.h"



/*! \file displaypurchases.h
 *  \brief A file outlining displaypurchases class methods.
 */



namespace Ui {
class displaypurchases;
}

/*!
 * \brief The displaypurchases class provides functionality to display transactions made during the current trip.
 *
 * The displaypurchases class has public inheritance of QDialog. The class is responsible for the display of all purchases
 * made during the trip. It also provides options to filter what is displayed on the main table by specific campus.
 */
class displaypurchases : public QDialog
{
    Q_OBJECT

public:
    explicit displaypurchases(QWidget *parent = nullptr, vector<Purchase>* purchaseList = nullptr);

    void populateTransactionTable( vector<Purchase>* purchaseList = nullptr, const QString& campus = "", bool displayAll = false);

    ~displaypurchases();

private slots:

    //!
    //! \brief on_closeButton_clicked
    //! Closes the current displaypurchases window.
    void on_closeButton_clicked();

    //!
    //! \brief on_displayButton_clicked
    //! Updates the main table of transaction data, applying the selected campus filter.
    void on_displayButton_clicked();

private:
    Ui::displaypurchases *ui;

    //!
    //! \brief allPurchases vector of Purchase objects holds all data for all purchases made during the current trip.
    //!
    vector<Purchase> allPurchases;
};

#endif // DISPLAYPURCHASES_H
