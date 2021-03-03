#include "initialfromuciform.h"
#include "ui_initialfromuciform.h"

initialFromUciForm::initialFromUciForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initialFromUciForm)
{

    totalDistance = 0;
    currentCampus.name = "University of California, Irvine (UCI)";
    currentCampus.number = 0;
    campusCount = 10;
    widgetCounter = 0;

    const QString FILE_NAME = "collegetouring.db";
    QString dbPath = qApp->applicationDirPath();
    dbPath.append('/' + FILE_NAME);

    // open database with file path
    database = new DbManager(dbPath);

    ui->setupUi(this);
}

initialFromUciForm::~initialFromUciForm()
{
    delete database;
    delete ui;
}

void initialFromUciForm::on_cancelTripButton_clicked()
{
    close(); // close this window
}

void initialFromUciForm::on_beginTripButton_clicked()
{
    vector<nameNumber> potentialVisits; // holds all campuses that can be visited from the current campus
    bool alreadyVisited = false;        // whether the current campus has already been visited in this route
    QString temp;                       // used to change labels

    // route begins at UCI
    route.push_back(currentCampus);

    // determine the complete route
    for (int i = 1; i <= campusCount; i++)
    {
        // collect all campuses that can be traveled to from currentCampus
        potentialVisits = database->getDistances(currentCampus.name);
        currentCampus = potentialVisits[0];

        // find the nearest campus from all potential visits
        for (int j = 0; j <= campusCount - 1; j++)
        {
            // check that the current campus has not already been previously visited in the route
            for (campusIterator = route.begin(); campusIterator < route.end(); campusIterator++)
            {
                if (potentialVisits[j].name == (*campusIterator).name)
                {
                    alreadyVisited = true;
                }
            }

            if (potentialVisits[j].number <= currentCampus.number && !alreadyVisited)
            {
                // currentCampus holds the closest potential visit
                currentCampus = potentialVisits[j];
            }

            alreadyVisited = false;
        }

        // next in route becomes the closest potential visit
        route.push_back(currentCampus);
        // add to the total distance
        totalDistance += currentCampus.number;
    }

    for (int i = 0; i < route.size(); i++)
     qDebug() << route[i].name;

    // prepare the next displayed widget

    ui->welcomeLabel->setText("Route Summary");

    ui->currentLabel->setText("Starting campus: ");
    ui->currentVarLabel->setText(route[0].name);

    ui->previousLabel->setText("Ending campus: ");
    ui->previousVarLabel->setText(route[campusCount].name);

    ui->distanceLabel->setText("Total distance: ");
    ui->distanceVarLabel->setText(QString::number(totalDistance));

    ui->imageLabel->setText("Listed below is the information for the entire trip. Click \"Next Campus\" to begin viewing each campus in the route individually in the order they were visited.");

    ui->initialFromUciStacked->setCurrentIndex(1);

}

void initialFromUciForm::on_exitButton_clicked()
{
    close(); // close this window
}

void initialFromUciForm::on_nextButton_clicked()
{

}
