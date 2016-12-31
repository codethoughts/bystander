#ifndef ACTIVITYFORM_H
#define ACTIVITYFORM_H

#include <QDialog>

#include "activity.h"

namespace Ui {
class ActivityForm;
}

class ActivityForm : public QDialog
{
    Q_OBJECT

private:
    Ui::ActivityForm *ui;
    Activity* activity;
public:
    explicit ActivityForm(QWidget *parent = 0);
    void setActivity(Activity*);
    ~ActivityForm();
private slots:
    void on_buttonBox_accepted();
};

#endif // EDITACTIVITYFORM_H
