#ifndef TRIPROUTEPLANNER_H
#define TRIPROUTEPLANNER_H

#include <QDialog>
#include <queue>
#include <list>
#include <QTextEdit>
#include "dbmanager.h"
#include "purchasewindow.h"
#include "displaypurchases.h"



/*! \file tripRoutePlanner.h
 *  \brief A file outlining tripRoutePlanner class methods.
 */



//!
//! \brief The TripType enum holds enumeration values for all available types of trips that can be taken.
//!
enum TripType {
    UCI,        /*!< The trip starts at University of California, Irvine and visits all campuses. */
    ASU,        /*!< The trip starts at Arizona State University and visits all selected campuses. */
    SADDLEBACK, /*!< The trip starts at Saddleback College and visits the initial 11 campuses. */
    CUSTOM      /*!< The trip is custom and is planned according to user input. */
};

namespace Ui { class tripRoutePlanner; }


/*!
 * \brief The tripRoutePlanner class provides functionality to plan and go on trips to several different college campuses.
 *
 * The tripRoutePlanner class has public inheritance of QDialog. The class is responsible for the display and function
 * of the trip planning features of the program. It alters its functionality for user input depending on whether a trip is predetermined
 * in its route or not. It also provides functionality to open souvenir purchase windows.
 */
class tripRoutePlanner : public QDialog
{
    Q_OBJECT

public:

    explicit tripRoutePlanner(QWidget *parent = nullptr, const TripType& = SADDLEBACK, DbManager* dbManager = nullptr, int visitNum = 11,
                              vector<QString> *visitList = nullptr);

    ~tripRoutePlanner();

    //!
    //! \brief createRoute
    //! recursively finds the campus that is closest to currentCampus, storing it into the route queue
    //! \param holds the name of the current campus
    //!
    void createRoute(QString campus);

private slots:

    //!
    //! \brief on_cancelTripButton_clicked
    //! closes the trip planning window when the button is clicked
    //!
    void on_cancelTripButton_clicked();

    //!
    //! \brief on_beginTripButton_clicked
    //! begins the trip, calculating the route and changing the display of the window to allow moving through each campus
    //!
    void on_beginTripButton_clicked();

    //!
    //! \brief on_exitButton_clicked
    //! closes the trip window when the button is clicked
    //!
    void on_exitButton_clicked();

    //!
    //! \brief on_nextButton_clicked
    //! changes window display to show information about the current campus in the route
    //!
    void on_nextButton_clicked();

    //!
    //! \brief on_souvenirsButton_clicked
    //! Opens the purchasewindow window to allow the user to purchase souvenirs specific to the currently visited campus.
    //!
    void on_souvenirsButton_clicked();

private:
    Ui::tripRoutePlanner *ui;

    //!
    //! \brief database used to access data stored in the database
    //!
    DbManager* database;

    purchasewindow* purchaseWindow;

    displaypurchases* displayPurchases;

    //!
    //! \brief initialCampus holds the name of the first campus in the trip
    //!
    QString initialCampus;

    //!
    //! \brief finalCampus holds the name of the last campus in the trip
    //!
    QString finalCampus;

    //!
    //! \brief currentCampus holds the name of the current campus in the trip
    //!
    QString currentCampus;

    //!
    //! \brief purchases holds all current purchases in the trip
    //!
    vector<Purchase> tripPurchases;

    //!
    //! \brief campusesToVisit holds all campuses that are planned to be visited in the current trip
    //!
    vector<QString> campusesToVisit;

    //!
    //! \brief route holds the campuses that are visited in the trip in order
    //!
    queue<QString> route;

    //!
    //! \brief totalDistance holds the total distance traveled in the entire trip
    //!
    double totalDistance;
};

#endif // TRIPROUTEPLANNER_H
