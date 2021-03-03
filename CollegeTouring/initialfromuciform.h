#ifndef INITIALFROMUCIFORM_H
#define INITIALFROMUCIFORM_H

#include <QDialog>
#include <dbmanager.h>

namespace Ui {
class initialFromUciForm;
}

class initialFromUciForm : public QDialog
{
    Q_OBJECT

public:
    explicit initialFromUciForm(QWidget *parent = nullptr);
    ~initialFromUciForm();

private slots:
    void on_cancelTripButton_clicked();

    void on_beginTripButton_clicked();

    void on_exitButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::initialFromUciForm *ui;

    DbManager* database;                         // database used to access campus data

    nameNumber currentCampus;                    // holds a current campus being evaluated
    vector<nameNumber> route;                    // holds campuses in order of the route
    vector<nameNumber> nextCampuses;             // holds campuses retrieved from database
    vector<nameNumber>::iterator campusIterator; // iterator for vector
    double totalDistance;                        // the total distance traveled during the route
    int campusCount;                             // the number of campuses being visited
    int widgetCounter;                           // used to track what is currently being displayed
};

#endif // INITIALFROMUCIFORM_H
