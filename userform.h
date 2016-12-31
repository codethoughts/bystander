#ifndef USERFROM_H
#define USERFROM_H

#include <QDialog>

#include "teacher.h"

namespace Ui {
class UserForm;
}

class UserForm : public QDialog
{
    Q_OBJECT

public:
    explicit UserForm(QWidget *parent = 0);
    ~UserForm();

    void setTeacher(Teacher* t);

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::UserForm *ui;
    Teacher* teacher;
};

#endif // EDITTEACHERFROM_H
