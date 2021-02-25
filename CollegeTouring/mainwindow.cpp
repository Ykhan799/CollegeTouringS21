#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbView = nullptr;
      
    ui->addCampusesButton->setVisible(false); // add campus button only visible to admin
    isAdmin = false; // initialize admin check to false
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Campus_Database_triggered()
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
{
    QString password; // IN   - the user entered password string

    // if the user is already an administrator, clicking the button will reverse it
    if (!isAdmin)
    {
        // retrieve the password from the text box and empty its contents
        password = ui->passwordEntry->text();
        ui->passwordEntry->setText("");

        // checking if the password is correct
        if (password == "AYEN" || password == "admin")
        {
            isAdmin = true;
            ui->loginButton->setText("Logout");
            ui->passwordEntry->setEnabled(false);

            // enable administrator functionality in the window
            ui->addCampusesButton->setVisible(true);
        }

        else
        {
            QMessageBox incorrectPassword;
            incorrectPassword.setWindowTitle("Incorrect password!");
            incorrectPassword.setText("The entered password is incorrect! Please try again with a valid password.");
            incorrectPassword.exec();
        }
    }

    else
    {
        isAdmin = false;

        ui->loginButton->setText("Log in as admin");
        ui->passwordEntry->setEnabled(true);

        // disable administrator functionality in the window
        ui->addCampusesButton->setVisible(false);
    }

}
