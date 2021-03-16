#include "campusselectdialog.h"
#include "ui_campusselectdialog.h"

CampusSelectDialog::CampusSelectDialog(QWidget *parent, vector<QString> campuses) :
    QDialog(parent),
    ui(new Ui::CampusSelectDialog)
{
    ui->setupUi(this);

    // populate QListWidget
    for(const auto& i: campuses) {
        ui->checkboxListWidget->addItem(i);
    }

    QListWidgetItem* item = nullptr;
    for(int i = 0; i < ui->checkboxListWidget->count(); ++i){
        item = ui->checkboxListWidget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }

}

CampusSelectDialog::~CampusSelectDialog()
{
    delete ui;
}

vector<QString> CampusSelectDialog::getChecked()
{
    vector<QString> checkedCampuses;

    //qDebug() << "rows: " << ui->checkboxListWidget->count();

    for (int i = 0; i < ui->checkboxListWidget->count(); ++i) {
        QListWidgetItem *item = ui->checkboxListWidget->item(i);

        //qDebug() << "item: " << item->text() << "checked: " << item->checkState();

        if(item->checkState() == Qt::Checked) {
            checkedCampuses.push_back(item->text());
            //qDebug() << item->text() << " is checked.";
            //qDebug() << checkedCampuses;
        }
        item = nullptr;
    }

    if(checkedCampuses.empty()) {
        checkedCampuses.push_back("EMPTY");
    }

    // qDebug() << checkedCampuses;

    return checkedCampuses;
}
