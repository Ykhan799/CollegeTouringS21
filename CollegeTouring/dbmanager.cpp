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

double DbManager::getDistance(const QString& currentCampus, const QString& nextCampus)
{
    QSqlQuery query;     // query

    double distance = 0; // distance between the two campuses

    // find the cell whose starting campus is currentCampus and whose ending campus is nextCampus
    query.prepare("SELECT DIST FROM CAMPUSES WHERE START = :CURRENTCAMPUS AND STOP = :NEXTCAMPUS");
    query.bindValue(":CURRENTCAMPUS", currentCampus);
    query.bindValue(":NEXTCAMPUS", nextCampus);

    // execute prepared query
    query.exec();

    // assign value to distance
    if (query.next())
    {
        distance = query.value(0).toDouble();
    }

    return distance;     // return distance

}

QSqlQueryModel* DbManager::getDistancesModel(const QString& campus) {
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;

    qDebug() << campus;

    query.prepare("SELECT START, STOP, DIST FROM CAMPUSES WHERE START = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    query.exec();

    model->setQuery(query);

    return model;
}

QSqlQueryModel* DbManager::getSouvenirsModel(const QString& campus) {
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;

    qDebug() << campus;

    query.prepare("SELECT CAMPUS, SOUVENIR, PRICE FROM SOUVENIRS WHERE CAMPUS = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    qDebug() << query.lastQuery();

    query.exec();

    model->setQuery(query);

    return model;
}
