#include "addcampuses.h"
#include "ui_addcampuses.h"
addcampuses::addcampuses(QWidget *parent, DbManager *database) :
    QDialog(parent),
    ui(new Ui::addcampuses)
{
    ui->setupUi(this);

    databaseExternal = database;

    if(databaseExternal == nullptr) {
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
        while (inFile)
        {
            getline(inFile, startingDist);
            getline(inFile, endingDist);
            inFile >> distance;
            inFile.ignore(10000, '\n');
            QString startDist = QString::fromStdString(startingDist);
            QString endDist = QString::fromStdString(endingDist);

            QSqlQuery query;
            query.prepare("SELECT max(ID) from CAMPUSES"); // get the maximum id from the table
            query.exec();

            // get the highest id from the bottom row of the table
            if(query.next()) {
                idNum =  query.value(0).toInt();
                idNum++;
                qDebug() << idNum;

                query.prepare("INSERT INTO CAMPUSES VALUES(:ID, :START, :STOP, :DIST)");
                query.bindValue(":ID", idNum); // id is the id of the bottom row + 1
                query.bindValue(":START", startDist);
                query.bindValue(":STOP", endDist);
                query.bindValue(":DIST", distance);

                success = query.exec();

                if(!success) {
                    qDebug() << "addCampus error: " << query.lastError();
                }

                else
                {
                    QMessageBox::information(this,QObject::tr("System Message"),tr("Campus distances have been added!"),QMessageBox::Ok);
                }

            } else {
                qDebug() << "Error: addCampus did not get an ID value from the table.";
            }
          }
         inFile.close();

        }
    }

void addcampuses::on_AddCampus_clicked()
{
    this->close();
}
