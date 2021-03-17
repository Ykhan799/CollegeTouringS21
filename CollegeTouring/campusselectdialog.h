#ifndef CAMPUSSELECTDIALOG_H
#define CAMPUSSELECTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <vector>

using namespace std;

namespace Ui {
class CampusSelectDialog;
}

class CampusSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CampusSelectDialog(QWidget *parent, vector<QString> campuses);
    ~CampusSelectDialog();

    //!
    //! \brief getChecked
    //! returns the checked campuses
    //! \return vector of selected campuses
    //!
    vector<QString> getChecked();

private slots:

private:
    Ui::CampusSelectDialog *ui;
};

#endif // CAMPUSSELECTDIALOG_H
