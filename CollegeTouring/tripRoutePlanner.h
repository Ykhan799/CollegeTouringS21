#ifndef TRIPROUTEPLANNER_H
#define TRIPROUTEPLANNER_H

#include <QDialog>
#include <queue>
#include <list>
#include "dbmanager.h"

enum TripType {
    UCI,
    ASU,
    SADDLEBACK,
    CUSTOM
};

namespace Ui { class tripRoutePlanner; }

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

private:
    Ui::tripRoutePlanner *ui;

    //!
    //! \brief database used to access data stored in the database
    //!
    DbManager* database;

    //!
    //! \brief initialCampus holds the name of the first campus in the trip
    //!
    QString initialCampus;

    //!
    //! \brief finalCampus holds the name of the last campus in the trip
    //!
    QString finalCampus;

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
