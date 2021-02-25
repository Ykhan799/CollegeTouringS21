#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbView = nullptr;
<<<<<<< HEAD
=======
      
    ui->addCampusesButton->setVisible(false); // add campus button only visible to admin
    isAdmin = false; // initialize admin check to false
>>>>>>> parent of 344f19d (Revert "Merge pull request #15 from gomihiko/distancedb")
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Campus_Database_triggered()
<<<<<<< HEAD
=======
{
    dbView = new databaseViewForm();
    dbView->exec();
    delete dbView;
    dbView = nullptr;
}

/*************************************************************************
 * void on_loginButton_clicked()
 * -----------------------------------------------------------------------
 * This function checks if an input password is valid when the log in
 * button is pressed. If the password is valid, administrator privileges
 * will be granted to the user and the button will afterwards function as a
 * logout button. Otherwise, a message box will be output alerting the user
 * that the password is incorrect and no other changes will be made. While
 * the user is an administrator, clicking the button will remove
 * administrator privileges and require the password to be entered again to
 * restore them.
 * -----------------------------------------------------------------------
 * Valid passwords:
 * AYEN
 * admin
 ************************************************************************/

void MainWindow::on_loginButton_clicked()
>>>>>>> parent of 344f19d (Revert "Merge pull request #15 from gomihiko/distancedb")
{
    dbView = new databaseViewForm();
    dbView->exec();
    delete dbView;
    dbView = nullptr;
}
