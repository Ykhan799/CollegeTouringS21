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

vector<nameNumber> DbManager::getDistances(const QString& campus)
{
    vector<nameNumber> nearbyCampuses;
    QSqlQuery query;
    int count = 0;

    // query database for campus names that hold distances from campus
    query.prepare("SELECT STOP FROM CAMPUSES WHERE START = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    query.exec();

    // add nameNumber obj to vector, each holds a name
    while (query.next())
    {
        QString out = query.value(0).toString();
        nameNumber current;
        current.name = out;
        nearbyCampuses.push_back(current);
    }
    // query database for distances from campus to each other campus stored in nearbyCampuses
    query.prepare("SELECT DIST FROM CAMPUSES WHERE START = :CAMPUS");
    query.bindValue(":CAMPUS", campus);

    query.exec();

    // iterating through vector, add a matching distance to the nameNumber objects
    while (query.next())
    {
        double outNum = query.value(0).toDouble();
        nearbyCampuses[count].number = outNum;
        count++;
    }

    return nearbyCampuses;
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
