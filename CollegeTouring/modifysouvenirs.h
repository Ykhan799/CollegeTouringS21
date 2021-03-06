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
    void on_modifyButton_clicked();

    void on_campusSouvenirComboBox_currentIndexChanged(const QString &arg1);

    void on_souvenirNameComboBox_currentIndexChanged(const QString &arg1);

    void on_deleteButton_clicked();

    void on_addButton_clicked();

private:
    Ui::modifySouvenirs *ui;

    DbManager* databaseInternal;
};

#endif // MODIFYSOUVENIRS_H
