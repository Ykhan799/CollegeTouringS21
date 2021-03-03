#include "modifysouvenirs.h"
#include "ui_modifysouvenirs.h"

modifySouvenirs::modifySouvenirs(QWidget *parent, DbManager* database) :
    QDialog(parent),
    ui(new Ui::modifySouvenirs)
{
    ui->setupUi(this);

    databaseInternal = database;

    if(databaseInternal == nullptr) {
        const QString FILE_NAME = "collegetouring.db";
        QString dbPath = qApp->applicationDirPath();
        dbPath.append('/' + FILE_NAME);

        // open database with file path
        databaseInternal = new DbManager(dbPath);
        qDebug() << "Database should be located at: " << dbPath;
    }

     // populate campuses combo box
    for(auto &i : databaseInternal->getCampusNames()) {
        ui->campusSouvenirComboBox->addItem(i);
    }

    // populate souvenirs once on window init
    //qDebug() << ui->campusSouvenirComboBox->currentText();
    ui->souvenirNameComboBox->clear();
    for(auto &i: databaseInternal->getSouvenirNamesByCampus(ui->campusSouvenirComboBox->currentText())) {
        ui->souvenirNameComboBox->addItem(i);
    }
}

modifySouvenirs::~modifySouvenirs()
{
    delete ui;
    databaseInternal = nullptr; // this is database review form's dbmanager, don't delete
}

void modifySouvenirs::on_pushButton_clicked()
{

}

void modifySouvenirs::on_campusSouvenirComboBox_currentIndexChanged(const QString &arg1)
{
    ui->souvenirNameComboBox->clear();
    // populate souvenirs once on window init
    //qDebug() << ui->campusSouvenirComboBox->currentText();
    for(auto &i: databaseInternal->getSouvenirNamesByCampus(ui->campusSouvenirComboBox->currentText())) {
        ui->souvenirNameComboBox->addItem(i);
    }
}

void modifySouvenirs::on_souvenirNameComboBox_currentIndexChanged(const QString &arg1)
{
    ui->nameLineEdit->setText(arg1);
    ui->priceSpinBox->setValue(databaseInternal->getSouvenirPrice(ui->souvenirNameComboBox->currentText(), ui->campusSouvenirComboBox->currentText()));
}
