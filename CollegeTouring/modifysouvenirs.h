#ifndef MODIFYSOUVENIRS_H
#define MODIFYSOUVENIRS_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include "dbmanager.h"

namespace Ui {
class modifySouvenirs;
}

class modifySouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit modifySouvenirs(QWidget *parent = nullptr, DbManager* database = nullptr);
    ~modifySouvenirs();

private slots:
    //!
    //! \brief on_modifyButton_clicked
    //! modifies a souvenir using data provided by UI elements
    void on_modifyButton_clicked();

    //!
    //! \brief on_campusSouvenirComboBox_currentIndexChanged
    //! updates the souvenir names in the modify/delete tab combo box
    //! \param arg1 currently unused
    //!
    void on_campusSouvenirComboBox_currentIndexChanged(const QString &arg1);

    //!
    //! \brief on_souvenirNameComboBox_currentIndexChanged
    //! updates the souvenir's price in the spin box
    //! \param arg1 currently unused
    //!
    void on_souvenirNameComboBox_currentIndexChanged(const QString &arg1);

    //!
    //! \brief on_deleteButton_clicked
    //! deletes the souvenir selected in the combo box
    void on_deleteButton_clicked();

    //!
    //! \brief on_addButton_clicked
    //! adds a souvenir based on the information given in the add souvenir tab
    void on_addButton_clicked();

private:
    Ui::modifySouvenirs *ui;

    //!
    //! \brief databaseInternal
    //! pointer to a DbManager object from the parent window
    DbManager* databaseInternal;
};

#endif // MODIFYSOUVENIRS_H
