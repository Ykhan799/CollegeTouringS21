#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    isLoggedIn = false;
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_logInButton_clicked()
{

    // Input data
    QString usernameInput = ui->usernameField->text();
    QString passwordInput = ui->passwordField->text();

    if(usernameInput == "Admin" && (passwordInput == "password" || passwordInput == "AYEN")) {
        QMessageBox::information(this, "Success", "Logged in as Administrator.");
        isLoggedIn = true;
        this->close();
    }else {
        QMessageBox::information(this, "Error", "Incorrect login information.");
        isLoggedIn = false;
    }
}

bool loginDialog::loggedIn() {
    return isLoggedIn;
}
