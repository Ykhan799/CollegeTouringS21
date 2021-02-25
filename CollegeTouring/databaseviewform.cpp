#include "databaseviewform.h"
#include "ui_databaseviewform.h"

databaseViewForm::databaseViewForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseViewForm)
{
    ui->setupUi(this);
    ui->distTableWidget->setColumnCount(2);
    ui->distTableWidget->setHorizontalHeaderLabels(QStringList{"Campus", "Distance"});
    ui->distTableWidget->setColumnWidth(0, 289);
    ui->distTableWidget->setColumnWidth(1, 289);

    ui->distTableWidget->setRowCount(1); // temp

    // populate combo box of colleges
    // for(...)
    // ui->collegeSelectBox->addItem(...)

    ui->collegeSelectBox->addItem("Saddleback College (temp)");

    // connect sqlite database to project
    campusDB = QSqlDatabase::addDatabase("QSQLITE");
    campusDB.setDatabaseName("PLACEHOLDER"); // TODO path to sqlite database
    if(!campusDB.open())
    {
        qDebug() << "\nError Opening Database\n";
    }

}

databaseViewForm::~databaseViewForm()
{
    delete ui;
}

void databaseViewForm::on_displayDistButton_clicked()
{
    // first clear the table
    ui->distTableWidget->clearContents();

    // temp
    ui->distTableWidget->setItem(0, 0, new QTableWidgetItem(QString("Hello")));
    ui->distTableWidget->setItem(0, 1, new QTableWidgetItem(QString("World")));

    // read from SQLite db here

    // fetch the number of rows needed to display the data and create the rows
    // ui->distTableWidget->setRowCount(1);

    // loop over the distances and select the distances from saddleback college and add them to an array/vector
    // sort the data

    // add to the table

}
