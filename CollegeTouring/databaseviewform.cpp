#include "databaseviewform.h"
#include "ui_databaseviewform.h"

databaseViewForm::databaseViewForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseViewForm)
{
    vector<QString> temp;

    const QString FILE_NAME = "collegetouring.db";
    QString dbPath = qApp->applicationDirPath();
    dbPath.append('/' + FILE_NAME);
    database = new DbManager(dbPath);

    ui->setupUi(this);

    temp = database->getCampusNames();
     // populate campuses combo box
    for(int i = 0; i < temp.size(); i++) {
        ui->collegeSelectBox->addItem(temp[i]);
    }

}

databaseViewForm::~databaseViewForm()
{
    delete ui;
    delete database;
}

void databaseViewForm::on_displayDistButton_clicked()
{
    if(ui->collegeSelectBox->currentText() == "") {
        QMessageBox::warning(this, "Error", "Please select a campus.");
    }else{
        qDebug() << "getting distances from " << ui->collegeSelectBox->currentText();

        auto model = database->getDistancesModel(ui->collegeSelectBox->currentText());

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Starting Campus"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Ending Campus"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Distance (mi)"));

        ui->campusesTableView->setModel(model);
        ui->campusesTableView->setColumnWidth(0,310);
        ui->campusesTableView->setColumnWidth(1,310);
        ui->campusesTableView->setColumnWidth(2,125);
    }

}
