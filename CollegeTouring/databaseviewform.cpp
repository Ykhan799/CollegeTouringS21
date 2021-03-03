#include "databaseviewform.h"
#include "ui_databaseviewform.h"

databaseViewForm::databaseViewForm(QWidget *parent, bool adminUser) :
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
    for(auto &i : database->getCampusNames()) {
        ui->collegeSelectBox->addItem(i);
        ui->collegeSelectBoxSouv->addItem(i);
    }

    // get admin status from main window
    isAdmin = adminUser;

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

void databaseViewForm::on_pushButton_clicked()
{
    // only admins can modify the database
    if(isAdmin) {
        modDialog = new modifySouvenirs(nullptr, database);
        modDialog->exec();
        delete modDialog;

        // update database model
        auto model = database->getSouvenirsModel(ui->collegeSelectBoxSouv->currentText());

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Campus"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Souvenir"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Price (USD)"));

        ui->souvenirTableView->setModel(model);
        ui->souvenirTableView->setColumnWidth(0,310);
        ui->souvenirTableView->setColumnWidth(1,310);
        ui->souvenirTableView->setColumnWidth(2,125);
    } else {
        QMessageBox error;
        QPixmap icon;
        icon.load(":/images/bonk_emoji.png");
        icon = icon.scaled(100,100);

        error.setText("Error!");
        error.setInformativeText("Only administrators may modify the database.");
        error.setStandardButtons(QMessageBox::Ok);
        error.setIconPixmap(icon);
        error.setWindowTitle("BONK!");
        error.exec();
    }
}
