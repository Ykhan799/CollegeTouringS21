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

private:
    Ui::modifySouvenirs *ui;

    DbManager* databaseInternal;
};

#endif // MODIFYSOUVENIRS_H
