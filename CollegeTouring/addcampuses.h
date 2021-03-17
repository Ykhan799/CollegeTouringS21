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
    //!
    //! \brief on_addFile_clicked
    //! Allows the administrator to add a text file in order to add campuses and distances
    //!
    void on_addFile_clicked();

    //!
    //! \brief on_AddCampus_clicked
    //! Closes the addcampuses window
    //!
    void on_AddCampus_clicked();
    
    //!
    //! \brief campusExists
    //! Checks if Campus is added.
    //! \param start - Starting campus
    //! \param end  - Ending Campus
    //! \param distance - Distance between the two campuses
    //! \return - True or False
    //!
    bool campusExists(QString& start, QString& end, double& distance);


private:
    Ui::addcampuses *ui;

    DbManager *databaseExternal;
};

#endif // ADDCAMPUSES_H
