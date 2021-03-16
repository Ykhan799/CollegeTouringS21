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

    //!
    //! \brief getInputNum
    //! \return inputNum, number input by the user
    //!
    int getInputNum() const { return inputNum;}

private slots:

    //!
    //! \brief on_buttonBox_accepted
    //! causes the dialog to close, stores the current value of the spinbox
    void on_buttonBox_accepted();

private:
    Ui::numberInputDialog *ui;

    //!
    //! \brief inputNum
    //! number from the spinbox when the dialog closes
    int inputNum;
};

#endif // NUMBERINPUTDIALOG_H
