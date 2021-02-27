#ifndef DATABASEVIEWFORM_H
#define DATABASEVIEWFORM_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include "dbmanager.h"

namespace Ui {
class databaseViewForm;
}

class databaseViewForm : public QDialog
{
    Q_OBJECT

public:
    explicit databaseViewForm(QWidget *parent = nullptr);
    ~databaseViewForm();

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

private:
    Ui::databaseViewForm *ui;

    DbManager* database;
};

#endif // DATABASEVIEWFORM_H
