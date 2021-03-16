#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbView = nullptr;
    //ui->addCampusesButton->setVisible(false); // add campus button only visible to admin

    isAdmin = false; // initialize admin check to false

    // initialize database manager object
    const QString FILE_NAME = "collegetouring.db";
    QString dbPath = qApp->applicationDirPath();
    dbPath.append('/' + FILE_NAME);

    // open database with file path
    database = new DbManager(dbPath);
    qDebug() << "Database should be located at: " << dbPath;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete database;
}

/*************************************************************************
 * void on_actionLog_In_triggered()
 * -----------------------------------------------------------------------
 * Creates a window which prompts the user for a username and password. If
 * entered correctly, the user will be granted admin privileges for the
 * remainder of the program execution unless the user chooses to log out.
 * -----------------------------------------------------------------------
 * Username: Admin
 *
 * Valid passwords:
 * AYEN
 * password
 ************************************************************************/
void MainWindow::on_actionLog_In_triggered()
{
    lDialog = new loginDialog();
    lDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinMaxButtonsHint);
    lDialog->exec();
    isAdmin = lDialog->loggedIn();
    delete lDialog;
}


/*************************************************************************
 * void on_actionLog_Out_triggered()
 * -----------------------------------------------------------------------
 * Creates a window which notifies the user they have been logged out. The
 * user is no longer considered an admin for the remainder of the program
 * execution unless the user successfully attempts to log in.
 ************************************************************************/

void MainWindow::on_actionLog_Out_triggered()
{
    isAdmin = false;
    QMessageBox::information(this, "Log Out", "You are now logged out.");
}

void MainWindow::on_actionView_Database_triggered()
{
    dbView = new databaseViewForm(nullptr, isAdmin);
    dbView->exec();
    delete dbView;
    dbView = nullptr;
}

/*************************************************************************
 * void on_actionVisit_local_colleges_UCI_triggered()
 * -----------------------------------------------------------------------
 * Creates a window to handle the planning and execution of a trip. This
 * trip begins at UCI and visits every closest campus to the current
 * campus until all colleges have been visited. There is no options for
 * the user to select their starting point. All initial 11 colleges are
 * visited.
 ************************************************************************/
void MainWindow::on_uciButton_clicked()
{
    // check for all 13 campuses here
    if((database->getCampusNames()).size() < 13) {
        QMessageBox::information(this, "Error", "Additional campuses have not been added to the database. Trip cannot be planned.");
    }else {
        tripPlannerWindow = new tripRoutePlanner(nullptr, UCI, database, 13);
        tripPlannerWindow->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
        tripPlannerWindow->exec();
        delete tripPlannerWindow;
    }
}

void MainWindow::on_asuButton_clicked()
{
    vector<QString> temp = database->getCampusNames();
    vector<QString> visitList;

    // remove ASU from the list of campuses
    for(auto i = temp.begin(); i < temp.end(); i++) {
        if(*i == "Arizona State University") {
            temp.erase(i);
        }
        }

    campusSelect = new CampusSelectDialog(nullptr, temp);
    campusSelect->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
    campusSelect->exec();
    visitList = campusSelect->getChecked();
    //qDebug() << visitList;

    delete campusSelect;

    if(visitList[0] == "EMPTY") {
        QMessageBox::information(this, "Error", "Please select at least one campus to visit.");
    }else {
        // re add ASU to the vector, order doesn't matter here
        visitList.push_back(visitList[0]);
        visitList[0] = "Arizona State University";

        // qDebug() << visitList;

        tripPlannerWindow = new tripRoutePlanner(nullptr, ASU, database, visitList.size(), &visitList);
        tripPlannerWindow->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
        tripPlannerWindow->exec();
        delete tripPlannerWindow;
    }

}

void MainWindow::on_saddlebackButton_clicked()
{
    tripPlannerWindow = new tripRoutePlanner(nullptr, SADDLEBACK, database, 11);
    tripPlannerWindow->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
    tripPlannerWindow->exec();

    delete tripPlannerWindow;
}
