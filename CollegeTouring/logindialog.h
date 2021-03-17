#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

    bool loggedIn();

private slots:

    //!
    //! \brief on_logInButton_clicked
    //! validates credentials from input widgets and logs user in if they are correct
    //!
    void on_logInButton_clicked();

private:
    Ui::loginDialog *ui;

    //!
    //! \brief isLoggedIn
    //! holds whether the user is logged in as an administrator.
    //!
    bool isLoggedIn;
};

#endif // LOGINDIALOG_H
