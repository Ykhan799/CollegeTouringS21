#include "tripRoutePlanner.h"
#include "ui_tripRoutePlanner.h"

tripRoutePlanner::tripRoutePlanner(QWidget *parent, const TripType& tripType, DbManager* dbManager, int visitNum, vector<QString> *visitList) :
    QDialog(parent),
    ui(new Ui::tripRoutePlanner)
{    
    vector<QString> temp;
    QString tempItinerary;

    // get database manager from parent class
    database = dbManager;

    // if a list was not provided, get list from database according to tripType
    if (visitList == nullptr)
    {
        // initialize member variables
        totalDistance = 0;
        temp = database->getCampusNames();

        switch(tripType) {
        case UCI: // if triptype is uci, visit the 13 campuses
            for(int i = 0; i < visitNum; i++) {
                campusesToVisit.push_back(temp[i]);
            }
            initialCampus = "University of California, Irvine (UCI)";
            break;

        case ASU: // if triptype is asu, visit selected number of campuses in shortest trip
            for(int i = 0; i < visitNum ; i++) {
                campusesToVisit.push_back(temp[i]);
            }
            initialCampus = "Arizona State University";
            break;

        case SADDLEBACK: // if tripType is saddleback, visit 11 campuses
            for(int i = 0; i < visitNum; i++) {
                campusesToVisit.push_back(temp[i]);
            }
            initialCampus = "Saddleback College";
            break;
        case CUSTOM: // if triptype is custom, open the custom triptype dialog
            break;
        }
    }
    else
    {
        // list is provided, so plan trip using data held in visitList
        campusesToVisit = *visitList;

        // verify all campuses in visitList exist in the database
        for (auto it = campusesToVisit.begin(); it != campusesToVisit.end(); it++)
        {
            if (!database->campusExists(*it))
            {
                // if an invalid campus is found, remove it from the list
                qDebug() << *it << " does not exist\n";
                campusesToVisit.erase(it);
                it--;
            }
        }

        if (!campusesToVisit.empty())
        {
            initialCampus = campusesToVisit.front();
        }
    }

    ui->setupUi(this);

    // populate the itinerary
    for(const auto& i : campusesToVisit) {
        tempItinerary += i;
        tempItinerary += '\n';
    }
    ui->collegesToVisitLabel->setText(tempItinerary);
    ui->startingCollegeLabel->setText("The following colleges will be visited in the most efficient order,\n starting at: " + initialCampus + '.');

}

tripRoutePlanner::~tripRoutePlanner()
{
    delete ui;
}

void tripRoutePlanner::createRoute(QString campus)
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

void tripRoutePlanner::on_cancelTripButton_clicked()
{
    tripRoutePlanner::close(); // close this window
}

void tripRoutePlanner::on_beginTripButton_clicked()
{
    if (campusesToVisit.empty())
    {
        tripRoutePlanner::close();
    }

    // determine the complete route
    createRoute(initialCampus);

    // begin viewing starting college in route

    on_nextButton_clicked();

    ui->initialFromUciStacked->setCurrentIndex(1);
}

void tripRoutePlanner::on_exitButton_clicked()
{
    tripRoutePlanner::close(); // close this window
}

void tripRoutePlanner::on_nextButton_clicked()
{
    // moves to next campus in the route while available
    if (!route.empty())
    {
        ui->welcomeLabel->setText(route.front());

        ui->nextLabel->setText("");

        ui->distanceLabel->setText("");

        currentCampus = route.front();

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
        ui->souvenirsButton->setText("Transactions");
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

void tripRoutePlanner::on_souvenirsButton_clicked()
{
    if (ui->souvenirsButton->text() != "Transactions")
    {
        purchaseWindow = new purchasewindow(nullptr, currentCampus);
        purchaseWindow->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
        purchaseWindow->exec();

        // add all new purchases to the running total of purchases in this trip
        for (auto it = purchaseWindow->purchases.begin(); it != purchaseWindow->purchases.end(); it++)
        {
            tripPurchases.push_back(*it);
        }

        delete purchaseWindow;
    }

    else
    {
        if (tripPurchases.empty())
        {
            QMessageBox::information(this, "Error!", "No transactions were made during this trip.");
        }
        else
        {
            vector<Purchase>* purchasesPtr = &tripPurchases;
            displayPurchases = new displaypurchases(nullptr, purchasesPtr);
            displayPurchases->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
            displayPurchases->exec();
            delete displayPurchases;
        }
    }
}
