#ifndef PATIENTSELECTDIALOG_H
#define PATIENTSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class PatientSelectDialog;
}

class PatientSelectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PatientSelectDialog(QWidget *parent = 0);
    ~PatientSelectDialog();
    
private:
    Ui::PatientSelectDialog *ui;
};

#endif // PATIENTSELECTDIALOG_H
