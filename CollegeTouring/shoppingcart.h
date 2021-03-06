#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QDialog>

namespace Ui {
class shoppingcart;
}

class shoppingcart : public QDialog
{
    Q_OBJECT

public:
    explicit shoppingcart(QWidget *parent = nullptr);
    ~shoppingcart();

private:
    Ui::shoppingcart *ui;
};

#endif // SHOPPINGCART_H
