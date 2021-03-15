#ifndef NUMBERINPUTDIALOG_H
#define NUMBERINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class numberInputDialog;
}

class numberInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit numberInputDialog(QWidget *parent = nullptr, QString prompt = "Placeholder Prompt", QString label = "Input");
    ~numberInputDialog();

    int getInputNum() const { return inputNum;}

private slots:
    void on_buttonBox_accepted();

private:
    Ui::numberInputDialog *ui;

    int inputNum;
};

#endif // NUMBERINPUTDIALOG_H
