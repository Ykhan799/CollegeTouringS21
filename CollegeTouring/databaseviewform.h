#ifndef DATABASEVIEWFORM_H
#define DATABASEVIEWFORM_H

#include <QDialog>

namespace Ui {
class databaseViewForm;
}

class databaseViewForm : public QDialog
{
    Q_OBJECT

public:
    explicit databaseViewForm(QWidget *parent = nullptr);
    ~databaseViewForm();

private slots:
    void on_displayDistButton_clicked();

private:
    Ui::databaseViewForm *ui;
};

#endif // DATABASEVIEWFORM_H
