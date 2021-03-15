#include "numberinputdialog.h"
#include "ui_numberinputdialog.h"

numberInputDialog::numberInputDialog(QWidget *parent, QString prompt, QString label) :
    QDialog(parent),
    ui(new Ui::numberInputDialog)
{
    ui->setupUi(this);
    ui->promptLabel->setText(prompt);
    ui->inputLabel->setText(label);

}

numberInputDialog::~numberInputDialog()
{
    delete ui;
}

void numberInputDialog::on_buttonBox_accepted()
{
    inputNum = ui->inputSpinBox->value();
}
