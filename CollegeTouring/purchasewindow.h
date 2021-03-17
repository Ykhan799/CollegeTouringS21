#ifndef PURCHASEWINDOW_H
#define PURCHASEWINDOW_H

#include <QDialog>
#include <vector>
#include <QMessageBox>
#include "dbmanager.h"



/*! \file purchasewindow.h
 *  \brief A file outlining purchasewindow class methods.
 */



//!
//! \brief The Purchase struct is used to construct an object which holds all necessary information about a purchase made by the user.
//!
struct Purchase
{
    //!
    //! \brief campusName holds the name of the campus where the purchase was made.
    //!
    QString campusName;

    //!
    //! \brief souvenirName holds the name of the souvenir that was selected during the purchase.
    //!
    QString souvenirName;

    //!
    //! \brief numberPurchased holds the quantity of souvenirs purchased.
    //!
    int numberPurchased;

    //!
    //! \brief price holds the cost of an individual purchased souvenir.
    //!
    double price;

    //!
    //! \brief totalSpent holds the total cost of the purchase.
    //!
    double totalSpent;
};

namespace Ui {
class purchasewindow;
}

/*!
 * \brief The purchasewindow class provides functionality to make purchases at a currently visited campus.
 *
 * The purchasewindow class has public inheritance of QDialog. The class is responsible for the display and function
 * of the souvenir purchasing feature of the program. It adjusts the display of available souvenir options where appropriate depending on the
 * types of souvenirs available at the current campus.
 */
class purchasewindow : public QDialog
{
    Q_OBJECT

public:
    explicit purchasewindow(QWidget *parent = nullptr, const QString& campus = "");
    ~purchasewindow();

    //!
    //! \brief purchases
    //! vector holds all purchases made during this session.
    //!
    vector<Purchase> purchases;

private slots:

    //!
    //! \brief on_purchaseButton_clicked
    //! Confirms the purchase of the currently selected item with the quantity entered by the user.
    void on_purchaseButton_clicked();

    //!
    //! \brief on_doneButton_clicked
    //! Closes the current purchasewindow window.
    void on_doneButton_clicked();

private:
    Ui::purchasewindow *ui;

    //!
    //! \brief database pointer to DbManager is used to access the program's database.
    //!
    DbManager *database;

    //!
    //! \brief currentCampus holds the name of the campus that this purchase is currently taking place at.
    //!
    QString currentCampus;

    //!
    //! \brief souvenirs vector holds the names of all souvenirs available at the current campus.
    //!
    vector<QString> souvenirs;
};

#endif // PURCHASEWINDOW_H
