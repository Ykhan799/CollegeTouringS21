#include "dbmanager.h"

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()) {
        qDebug() << "Error: could not connect to database.";
    }else {
        qDebug() << "Database connection OK";
    }
}

vector<QString> DbManager::getCampusNames() {
    vector<QString> names;

    // query database for campus names
    QSqlQuery query("SELECT DISTINCT START FROM CAMPUSES");

     // add campus names to vector (unique)
    while(query.next()) {
        QString out = query.value(0).toString();
        names.push_back(out);
    }

    return names;
}

vector<QString> DbManager::getSouvenirNamesByCampus(const QString &campus)
{
    vector<QString> souvenirs;
    QSqlQuery query;

    // query database for souvenirs by campus
    query.prepare("SELECT SOUVENIR FROM SOUVENIRS WHERE CAMPUS = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    query.exec();

     // add souvenir names to vector
    while(query.next()) {
        QString out = query.value(0).toString();
        souvenirs.push_back(out);
    }

    return souvenirs;
}

QSqlQueryModel* DbManager::getDistancesModel(const QString& campus) {
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;

    //qDebug() << campus;

    query.prepare("SELECT START, STOP, DIST FROM CAMPUSES WHERE START = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    query.exec();

    model->setQuery(query);

    return model;
}

QSqlQueryModel* DbManager::getSouvenirsModel(const QString& campus) {
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;

    //qDebug() << campus;

    query.prepare("SELECT CAMPUS, SOUVENIR, PRICE FROM SOUVENIRS WHERE CAMPUS = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    //qDebug() << query.lastQuery();

    query.exec();

    model->setQuery(query);

    return model;
}

double DbManager::getSouvenirPrice(const QString &souvenir, const QString &campus)
{
    QSqlQuery query;

    query.prepare("SELECT PRICE FROM SOUVENIRS WHERE SOUVENIR = :SOUVENIR AND CAMPUS = :CAMPUS");
    query.bindValue(":SOUVENIR", souvenir);
    query.bindValue(":CAMPUS", campus);

    query.exec();

    if(query.next()) {

        QString out = query.value(0).toString();
        //qDebug() << "souvenir price: " << out;

        return query.value(0).toDouble();
    }else {
        qDebug() << "No Result.";
        return -1;
    }
}

void DbManager::updateSouvenir(const QString& campus, const QString& oldName, const QString &newName, const double &newPrice)
{
    QSqlQuery query;
    bool success;

    query.prepare("UPDATE SOUVENIRS SET PRICE = :NEWPRICE, SOUVENIR = :NEWNAME WHERE CAMPUS = :CAMPUS AND SOUVENIR = :OLDNAME");
    query.bindValue(":NEWPRICE", newPrice);
    query.bindValue(":NEWNAME", newName);
    query.bindValue(":CAMPUS", campus);
    query.bindValue(":OLDNAME", oldName);

    // qDebug() << "bound: " << query.boundValues();

    success = query.exec();

    if(!success) {
        qDebug() << "updateSouvenir error: " << query.lastError();
    }
}

void DbManager::removeSouvenir(const QString &campus, const QString &souvenirName)
{
    QSqlQuery query;
    bool success;

    query.prepare("DELETE FROM SOUVENIRS WHERE CAMPUS = :CAMPUS AND SOUVENIR = :SOUVENIRNAME");
    query.bindValue(":CAMPUS", campus);
    query.bindValue(":SOUVENIRNAME", souvenirName);

    // qDebug() << "bound: " << query.boundValues();

    success = query.exec();

    if(!success) {
        qDebug() << "removeSouvenir error: " << query.lastError();
    }
}

void DbManager::addSouvenir(const QString &campus, const QString &souvenirName, const double &price)
{
    QSqlQuery query;
    int maxID;
    bool success;

    query.prepare("SELECT max(ID) from SOUVENIRS"); // get the maximum id from the table
    query.exec();

    // get the highest id from the bottom row of the table
    if(query.next()) {
        maxID =  query.value(0).toInt();
        maxID++;
        qDebug() << maxID;

        query.prepare("INSERT INTO SOUVENIRS VALUES(:ID, :CAMPUS, :SOUVENIRNAME, :SOUVENIRPRICE)");
        query.bindValue(":ID", maxID); // id is the id of the bottom row + 1
        query.bindValue(":CAMPUS", campus);
        query.bindValue(":SOUVENIRNAME", souvenirName);
        query.bindValue(":SOUVENIRPRICE", price);

        success = query.exec();

        if(!success) {
            qDebug() << "addSouvenir error: " << query.lastError();
        }

    } else {
        qDebug() << "Error: addSouvenir did not get an ID value from the table.";
    }

}

