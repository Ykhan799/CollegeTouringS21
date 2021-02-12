#include "databaseviewform.h"
#include "ui_databaseviewform.h"

databaseViewForm::databaseViewForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseViewForm)
{
    ui->setupUi(this);
    ui->distTableWidget->setColumnCount(2);
    ui->distTableWidget->setRowCount(1);
    ui->distTableWidget->setColumnWidth(0, 289);
    ui->distTableWidget->setColumnWidth(1, 289);
}

databaseViewForm::~databaseViewForm()
{
    delete ui;
}

void databaseViewForm::on_displayDistButton_clicked()
{
    ui->distTableWidget->setItem(0, 0, new QTableWidgetItem(QString("Hello")));
    ui->distTableWidget->setItem(0, 1, new QTableWidgetItem(QString("World")));
}
