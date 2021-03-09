#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <databaseviewform.h>
#include <logindialog.h>
#include <initialfromuciform.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLog_In_triggered();

    void on_actionLog_Out_triggered();

    void on_actionView_Database_triggered();

    void on_actionVisit_local_colleges_UCI_triggered();

    void on_uciButton_clicked();

private:
    Ui::MainWindow *ui;
    databaseViewForm* dbView;
    loginDialog* lDialog;
    initialFromUciForm* initialFromUci;


    bool isAdmin;
};
#endif // MAINWINDOW_H
