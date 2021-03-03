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

    // open database with file path
    database = new DbManager(dbPath);
    qDebug() << "Database should be located at: " << dbPath;

    ui->setupUi(this);

    temp = database->getCampusNames();
     // populate campuses combo box
    for(int i = 0; i < temp.size(); i++) {
        ui->collegeSelectBox->addItem(temp[i]);
        ui->collegeSelectBoxSouv->addItem(temp[i]);
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

void databaseViewForm::on_displaySouvButton_clicked()
{
    if(ui->collegeSelectBox->currentText() == "") {
        QMessageBox::warning(this, "Error", "Please select a campus.");
    }else{
        qDebug() << "getting souvenirs from " << ui->collegeSelectBoxSouv->currentText();

        auto model = database->getSouvenirsModel(ui->collegeSelectBoxSouv->currentText());

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Campus"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Souvenir"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price (USD)"));

        ui->souvenirTableView->setModel(model);
        ui->souvenirTableView->setColumnWidth(0,310);
        ui->souvenirTableView->setColumnWidth(1,310);
        ui->souvenirTableView->setColumnWidth(2,125);
    }
}

/*
// Not completed yet. User must be an admin to add campuses
void databaseViewForm::on_addCampuses_clicked()
{
    //login = new loginDialog(this);
    bool isAdmin = true;
    if (isAdmin == false)
    {
        QMessageBox::warning(this, "Error", "Only Admin can add campuses.");
    }
    else
    {
        addcampus = new addcampuses(this);
        addcampus->show();
    }
}
*/


/*std::vector<QString> databaseViewForm::getActiveTableRow()
{

}*/

void databaseViewForm::on_showCartButton_clicked()
{
   cart = new shoppingcart(this);
   cart->show();
}
