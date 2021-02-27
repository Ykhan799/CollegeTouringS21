#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QTableView>

#include <vector>
#include <algorithm>

using namespace std;

class DbManager
{
public:
    //!
    //! \brief DbManager
    //! \param path - path to SQLite database
    //!
    DbManager(const QString& path);

    //!
    //! \brief getCampusNames
    //! \return QString vector of unique campus names
    //!
    vector<QString> getCampusNames();

    //!
    //! \brief getDistancesModel
    //! \param campus name of campus to get distances to
    //! \return model containing campus names and distances
    //!
    QSqlQueryModel* getDistancesModel(const QString& campus);

    //!
    //! \brief getSouvenirsModel
    //! \param campus name of campus to return souvenirs from
    //! \return model containing campus names, souvenirs, and prices
    //!
    QSqlQueryModel* getSouvenirsModel(const QString& campus);
private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
