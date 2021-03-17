#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "dbmanager.h"
#include "databaseviewform.h"
#include "logindialog.h"
#include "tripRoutePlanner.h"
#include "numberinputdialog.h"
#include "campusselectdialog.h"


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
    //!
    //! \brief on_actionLog_In_triggered
    //! launches the log in window
    //!
    void on_actionLog_In_triggered();

    //!
    //! \brief on_actionLog_Out_triggered
    //! logs the user out (no log in window)
    //!
    void on_actionLog_Out_triggered();

    //!
    //! \brief on_actionView_Database_triggered
    //! launches the database view window
    //!
    void on_actionView_Database_triggered();

    //!
    //! \brief on_uciButton_clicked
    //! launches the trip planner, planning a UCI trip
    //!
    void on_uciButton_clicked();

    //!
    //! \brief on_asuButton_clicked
    //! launches the trip planner, planning an ASU trip
    //!
    void on_asuButton_clicked();

    //!
    //! \brief on_saddlebackButton_clicked
    //! launches the trip planner, planning a saddleback trip
    //!
    void on_saddlebackButton_clicked();

    //!
    //! \brief on_customButton_clicked
    //! launches the trip planner, planning a custom trip
    //!
    void on_customButton_clicked();

private:
    Ui::MainWindow *ui;
    databaseViewForm* dbView;
    loginDialog* lDialog;
    tripRoutePlanner* tripPlannerWindow;
    DbManager* database;
    numberInputDialog* inputDialog;
    CampusSelectDialog* campusSelect;

    bool isAdmin;
};
#endif // MAINWINDOW_H
