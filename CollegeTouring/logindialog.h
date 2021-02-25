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
    void on_logInButton_clicked();

private:
    Ui::loginDialog *ui;

    bool isLoggedIn;
};

#endif // LOGINDIALOG_H
