#include <QWidget>
#include <QtGui>
#include <QMessageBox>

#include "activity.h"
#include "teacher.h"

#include "file_delegator.hpp"
#include "activityreference.h"

#include "userform.h"
#include "ui_userform.h"


extern ActivityReference activities;
extern Delegator<Teacher> teachers;

UserForm::UserForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserForm)
{
    ui->setupUi(this);

    teacher = nullptr;

    for (auto a : activities.getActivities())
    {
        ui->activitiesComboBox->addItem(QString().number(a.getID())
                + " " + a.getTitle());
    }
}

UserForm::~UserForm()
{
    delete ui;
}


void UserForm::setTeacher(Teacher* t)
{
    ui->tabWidget->removeTab(1);

    teacher = t;
    Activity* a = activities.findActivityByInnerID(t);

    ui->name_t->setText(teacher->getName());
    ui->username_t->setText(teacher->getUsername());
    ui->password_t->setText(teacher->getPassword());
    ui->email_t->setText(teacher->getEmail());


    // In case if teacher has activity
    if (a != nullptr)
    {   
        int index = activities.getActivities().indexOf(*a);

        ui->title->setText(a->getTitle());
        ui->desc->setText(a->getDescription());

        ui->startDate->setDate(a->getStartDate().date());
        ui->startTime->setTime(a->getStartDate().time());

        ui->endDate->setDate(a->getEndDate().date());
        ui->endTime->setTime(a->getEndDate().time());

        ui->fee->setValue(a->getFee());

        ui->activitiesComboBox->setCurrentIndex(index + 1);
    }
}

void UserForm::on_tabWidget_currentChanged(int index)
{

}

void UserForm::on_buttonBox_accepted()
{
    QMessageBox* box = new QMessageBox(this);
    box->setText("Congratulations!");

    QRegularExpression re("(?<!.)\\b\\d+\\b");
    QRegularExpressionMatch m = re.match(ui->activitiesComboBox
            ->currentText());

    quint32 a_id = m.captured().toInt();

    Activity* activity = new Activity();
    activity->setID(a_id);


    if (teacher == nullptr) {

        teacher = new Teacher(ui->username_t->text(),
                              ui->password_t->text(),
                              ui->name_t->text(),
                              ui->email_t->text());

        box->setInformativeText("Teacher "
                                + teacher->getUsername()
                                + " was succesfully created!");

    } else {

        teacher->setUsername(ui->username_t->text());
        teacher->setPassword(ui->password_t->text());
        teacher->setName(ui->name_t->text());
        teacher->setEmail(ui->email_t->text());

        box->setInformativeText("Teacher "
                                + teacher->getUsername()
                                + " was succesfully updated!");
    }

    teacher->setActivityID(a_id);
    activities.assign(activity, teacher);

    box->show();
}
