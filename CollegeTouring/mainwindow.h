#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <databaseviewform.h>

#include <databaseviewform.h>

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
<<<<<<< HEAD
    void on_actionOpen_Campus_Database_triggered();
=======

    void on_loginButton_clicked();
>>>>>>> parent of 344f19d (Revert "Merge pull request #15 from gomihiko/distancedb")

private:
    Ui::MainWindow *ui;
    databaseViewForm* dbView;
};
#endif // MAINWINDOW_H
