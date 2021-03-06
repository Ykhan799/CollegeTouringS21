#include "shoppingcart.h"
#include "ui_shoppingcart.h"

shoppingcart::shoppingcart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shoppingcart)
{
    ui->setupUi(this);
}

shoppingcart::~shoppingcart()
{
    delete ui;
}
