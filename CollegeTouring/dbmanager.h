#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QTableView>

#include <vector>
#include <algorithm>

#include <structcontainer.h>

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
    //! \brief getDistances returns the distance from campus to all other campusese in the database
    //! \param campus is the name of the campus to get distances from
    //! \return vector of objects holding the name of the campus and the distance from the passed campus
    //!
    vector<nameNumber> getDistances(const QString& campus);

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
