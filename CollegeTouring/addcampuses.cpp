#include "addcampuses.h"
#include "ui_addcampuses.h"
addcampuses::addcampuses(QWidget *parent, DbManager *database) :
    QDialog(parent),
    ui(new Ui::addcampuses)
{
    ui->setupUi(this);

    databaseExternal = database;

    if(!databaseExternal) {
        const QString FILE_NAME = "collegetouring.db";
        QString dbPath = qApp->applicationDirPath();
        dbPath.append('/' + FILE_NAME);

        // open database with file path
        databaseExternal = new DbManager(dbPath);
        qDebug() << "Database should be located at: " << dbPath;
    }
}

addcampuses::~addcampuses()
{
    delete ui;
    databaseExternal = nullptr;

}

void addcampuses::on_addFile_clicked()
{
    string startingDist;
    string endingDist;
    double distance;
    int idNum;
    bool success;

    // Opens up file on computer
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/Downloads", tr("Txt Files (*.txt)"));
    QFile file(fileName);

    std::ifstream inFile;
    inFile.open(fileName.toStdString());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, QObject::tr("System Message"), tr("File cannot be found. Add a different file"));
    }

    else
    {
        while (!inFile.eof() && inFile.peek() != '\n')
        {
            // reads the two campuses and distances
            getline(inFile, startingDist);
            getline(inFile, endingDist);
            inFile >> distance;
            inFile.ignore(10000, '\n');

            // gets the starting and ending campus
            QString startDist = QString::fromStdString(startingDist);
            QString endDist = QString::fromStdString(endingDist);
                 
            // Checks if a given campus exists 
                if (campusExists(startDist, endDist, distance))
                {
                    //QMessageBox::warning(this, "Error", "Campus Exists");
                    break;
                }
                QSqlQuery query;
                query.prepare("SELECT max(ID) from CAMPUSES"); // get the maximum id from the table
                query.exec();

                // get the highest id from the bottom row of the table
                if(query.next()) {
                    idNum =  query.value(0).toInt();
                    idNum++;
                    qDebug() << idNum;

                    // Adds into campuses and distance into database
                    query.prepare("INSERT INTO CAMPUSES VALUES(:ID, :START, :STOP, :DIST)");
                    query.bindValue(":ID", idNum); // id is the id of the bottom row + 1
                    query.bindValue(":START", startDist);
                    query.bindValue(":STOP", endDist);
                    query.bindValue(":DIST", distance);

                    success = query.exec();

                    if(!success) {
                        qDebug() << "addCampus error: " << query.lastError();
                    }

                } else {
                    qDebug() << "Error: addCampus did not get an ID value from the table.";
                }

          }
        // closes file
         inFile.close();
    }
}

void addcampuses::on_AddCampus_clicked()
{
    this->close();
}

bool addcampuses::campusExists(QString& start, QString& end, double& distance)
{
    QSqlQuery query;
    bool success;
    bool found;

    query.prepare("SELECT EXISTS(SELECT 1 FROM CAMPUSES WHERE START=:START AND STOP=:STOP AND DIST=:DIST)");
    query.bindValue(":START", start);
    query.bindValue(":STOP", end);
    query.bindValue(":DIST", distance);

    success = query.exec();

    if(!success) {
          qDebug() << "campusExists error: " << query.lastError();
          return false;
    }

    query.first();
    found = query.value(0).toBool();

    //qDebug() << "found: " << found;

    return found;
}
