#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "dbmanager.h"
#include "databaseviewform.h"
#include "logindialog.h"
#include "tripRoutePlanner.h"


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

    void on_uciButton_clicked();

    void on_asuButton_clicked();

    void on_saddlebackButton_clicked();

private:
    Ui::MainWindow *ui;
    databaseViewForm* dbView;
    loginDialog* lDialog;
    tripRoutePlanner* tripPlannerWindow;
    DbManager* database;


    bool isAdmin;
};
#endif // MAINWINDOW_H
