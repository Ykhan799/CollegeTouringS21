#ifndef ADDCAMPUSES_H
#define ADDCAMPUSES_H

#include <QDialog>
#include "ui_addcampuses.h"
#include "dbmanager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QFile>
#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDir>
using namespace std;
namespace Ui {
class addcampuses;
}

class addcampuses : public QDialog
{
    Q_OBJECT

public:
    explicit addcampuses(QWidget *parent = nullptr, DbManager *database = nullptr);
    ~addcampuses();

private slots:
    // Need to do DOxygen
    void on_addFile_clicked();
    // Need to do DOxygen
    void on_AddCampus_clicked();

private:
    Ui::addcampuses *ui;

    DbManager *databaseExternal;
};

#endif // ADDCAMPUSES_H
