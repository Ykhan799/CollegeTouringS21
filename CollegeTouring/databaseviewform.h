#ifndef DATABASEVIEWFORM_H
#define DATABASEVIEWFORM_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include "dbmanager.h"
#include "shoppingcart.h"
#include <vector>
namespace Ui {
class databaseViewForm;
}

class databaseViewForm : public QDialog
{
    Q_OBJECT

public:
    explicit databaseViewForm(QWidget *parent = nullptr);
    ~databaseViewForm();
    std::vector<QString> getActiveTableRow();

private slots:
    //!
    //! \brief on_displayDistButton_clicked
    //! populates the table with distances when the button is clicked
    //!
    void on_displayDistButton_clicked();

    //!
    //! \brief on_displaySouvButton_clicked
    //! populates the table with souvenirs when the button is clicked
    void on_displaySouvButton_clicked();

    void on_showCartButton_clicked();

private:
    Ui::databaseViewForm *ui;

    DbManager* database;

    shoppingcart *cart;

};

#endif // DATABASEVIEWFORM_H
