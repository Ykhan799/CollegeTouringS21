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
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*************************************************************************
 * void on_login_triggered()
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
void MainWindow::on_actionLog_In_triggered()
{
    lDialog = new loginDialog();
    lDialog->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint & ~Qt::WindowMinMaxButtonsHint);
    lDialog->exec();
    isAdmin = lDialog->loggedIn();
    delete lDialog;
}

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
