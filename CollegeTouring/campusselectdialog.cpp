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

vector<QString> CampusSelectDialog::getChecked() const
{
    auto temp = ui->checkboxListWidget->selectedItems();
    vector<QString> returnCampuses;


    for(const auto& i : temp) {
        returnCampuses.push_back(i->text());
    }

    return returnCampuses; // dummy
}
