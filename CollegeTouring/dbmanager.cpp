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

