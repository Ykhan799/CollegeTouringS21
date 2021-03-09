#include "initialfromuciform.h"
#include "ui_initialfromuciform.h"

initialFromUciForm::initialFromUciForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::initialFromUciForm)
{
    const QString FILE_NAME = "collegetouring.db";
    QString dbPath = qApp->applicationDirPath();
    dbPath.append('/' + FILE_NAME);

    // open database with file path
    database = new DbManager(dbPath);

    // initialize member variables
    totalDistance = 0;
    campusesToVisit = database->getCampusNames();

    initialCampus = "University of California, Irvine (UCI)";


    ui->setupUi(this);
}

initialFromUciForm::~initialFromUciForm()
{
    delete database;
    delete ui;
}

void initialFromUciForm::createRoute(QString campus)
{
    // add the campus to the route queue
    route.push(campus);

    // remove the campus from the list of campuses that still need to be visited
    auto it = std::find(campusesToVisit.begin(), campusesToVisit.end(), campus);
    if (it != campusesToVisit.end())
    {
        campusesToVisit.erase(it);
    }

    // base case, no more campuses to visit in this route
    if (campusesToVisit.size() <= 0)
    {
        // assign this campus to finalCampus and exit function
        finalCampus = campus;
        return;
    }

    else
    {
        // initialize variables to hold closest campus
        QString closestCampus = campusesToVisit.front();
        double shortestDist = database->getDistance( campus, campusesToVisit.front() );
        auto it = campusesToVisit.begin();

        while (it != campusesToVisit.end())
        {
            // update the closest campus if the currently accessed campus in the vector is closer than previous closest campus
            if (database->getDistance(campus, *it) < shortestDist)
            {
                closestCampus = *it;
                shortestDist = database->getDistance( campus, *it );
            }

            // increment iterator
            it++;
        }

        // finally add to the total distance counter
        totalDistance += shortestDist;

        // recursive call
        createRoute(closestCampus);
    }
}

void initialFromUciForm::on_cancelTripButton_clicked()
{
    close(); // close this window
}

void initialFromUciForm::on_beginTripButton_clicked()
{

    // determine the complete route
    createRoute(initialCampus);

    // begin viewing starting college in route

    on_nextButton_clicked();

    ui->initialFromUciStacked->setCurrentIndex(1);

}

void initialFromUciForm::on_exitButton_clicked()
{
    close(); // close this window
}

void initialFromUciForm::on_nextButton_clicked()
{
    // moves to next campus in the route while available
    if (!route.empty())
    {
        ui->welcomeLabel->setText(route.front());

        ui->nextLabel->setText("");

        ui->distanceLabel->setText("");

        route.pop();

        if (route.empty())
        {
            ui->nextButton->setText("Finish Trip");
        }
    }
    // when all campuses have been seen, change window to summary page
    else
    {
        ui->nextButton->setVisible(false);
        ui->souvenirsButton->setVisible(false);
        ui->exitButton->setText("Exit");
        ui->welcomeLabel->setText("Route Summary");

        ui->nextLabel->setText("Starting campus: ");
        ui->nextVarLabel->setText(initialCampus);

        ui->previousLabel->setText("Ending campus: ");
        ui->previousVarLabel->setText(finalCampus);

        ui->distanceLabel->setText("Total distance traveled: ");
        ui->distanceVarLabel->setText(QString::number(totalDistance));

        ui->unitsLabel->setText("miles");

    }

}
