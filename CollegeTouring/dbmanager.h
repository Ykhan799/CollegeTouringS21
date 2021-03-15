#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
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
    //! \brief getDistance returns the distance between currentCampus and nextCampus
    //! \param currentCampus is the name of the originating campus
    //! \param nextCampus is the name of the campus to be traveled to
    //! \return a double value holding the distance from currentCampus to nextCampus
    //!
    double getDistance(const QString& currentCampus, const QString& nextCampus);
  
    //! \brief getSouvenirNamesByCampus
    //! \param campus campus name to get souvenirs from
    //! \return vector containng souvenir names
    //!
    vector<QString> getSouvenirNamesByCampus(const QString& campus);

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

    //!
    //! \brief getSouvenirPrice
    //! \param souvenir name of souvenir
    //! \param campus campus that the souvenir is from
    //! \return price of the provided souvenir from the database
    //!
    double getSouvenirPrice(const QString& souvenir, const QString& campus);

    //!
    //! \brief updateSouvenir
    //! \param campus campus souvenir belongs to
    //! \param oldName souvenir's old name
    //! \param newName souvenir's new name
    //! \param newPrice souvenir's new price
    //!
    void updateSouvenir(const QString& campus, const QString& oldName, const QString &newName, const double &newPrice);

    //!
    //! \brief removeSouvenir
    //! \param campus campus souvenir belongs to
    //! \param souvenirName name of souvenir to remove
    //!
    void removeSouvenir(const QString& campus, const QString& souvenirName);

    //!
    //! \brief addSouvenir
    //! \param campus campus souvenir belongs to
    //! \param souvenirName name of new souvenir
    //! \param price price of new souvenir
    //!
    void addSouvenir(const QString& campus, const QString& souvenirName, const double& price);

    //!
    //! \brief souvExists
    //! checks if a souvenir exists
    //! \param campus campus that souvenir belongs to
    //! \param souvenirName souvenir to check for
    //! \return true if souvenir exists for a certain campus
    //!
    bool souvExists(QString& campus, QString& souvenirName);

    //!
    //! \brief campusExists
    //! checks if a campus name exists
    //! \param campus name of the campus to look for
    //! \return true if the campus name is found in the database
    //!
    bool campusExists(QString& campus);

    //!
    //! \brief getInitialCampusNames
    //! \return QString vector of unique campus names ONLY campuses 1 - 11
    //!
    vector<QString> getInitialCampusNames();

private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
