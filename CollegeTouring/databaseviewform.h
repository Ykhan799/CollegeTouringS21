#ifndef DATABASEVIEWFORM_H
#define DATABASEVIEWFORM_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QPixmap>
#include "dbmanager.h"
#include "modifysouvenirs.h"

namespace Ui {
class databaseViewForm;
}

class databaseViewForm : public QDialog
{
    Q_OBJECT

public:
    explicit databaseViewForm(QWidget *parent = nullptr, bool adminUser = false);
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

    //!
    //! \brief on_pushButton_clicked
    //! opens the modify database menu ONLY if user is an administrator.
    void on_pushButton_clicked();

private:
    Ui::databaseViewForm *ui;

    DbManager* database;
    modifySouvenirs* modDialog;

    bool isAdmin;
};

#endif // DATABASEVIEWFORM_H
