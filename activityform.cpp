#include <QWidget>
#include <QDialog>
#include <climits>
#include <QMessageBox>

#include "teacher.h"
#include "activity.h"

#include "file_delegator.hpp"
#include "activityreference.h"

#include "activityform.h"
#include "ui_activityform.h"

extern ActivityReference activities;

ActivityForm::ActivityForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivityForm)
{
    ui->setupUi(this);

    for(auto t : teachers.data()) {
        ui->TeachersComboBox->addItem(t.getUsername());
    }

    ui->startDate->setDateTime(QDateTime().currentDateTime());
    ui->endDate->setDateTime(QDateTime().currentDateTime().addDays(2).addSecs(7200));

    activity = nullptr;
}


void ActivityForm::setActivity(Activity* a)
{
    activity = a;
    Teacher* t = activities.getTeacher(a);

    ui->title->setText(activity->getTitle());
    ui->description->setText(activity->getDescription());
    ui->startDate->setDateTime(activity->getStartDate());
    ui->endDate->setDateTime(activity->getEndDate());
    ui->fee->setValue(activity->getFee());

    if (t != nullptr) {
        int index = teachers.data().indexOf(*t);
        ui->TeachersComboBox->setCurrentIndex(index + 1);
    }
}

ActivityForm::~ActivityForm()
{
    delete ui;
}

void ActivityForm::on_buttonBox_accepted()
{
    int index = ui->TeachersComboBox->currentIndex();

    QMessageBox* box = new QMessageBox(this);
    box->setText("Congratulations!");

    Teacher* teacher;

    // if edit
    if (activity != nullptr) {

        activity->setTitle(ui->title->text());
        activity->setDescription(ui->description->toPlainText());
        activity->setStartDate(ui->startDate->dateTime());
        activity->setEndDate(ui->endDate->dateTime());
        activity->setFee(ui->fee->value());


        // if teacher selected
        if (index) {
            teacher = teachers.getElementAt(index - 1);
            activities.assign(activity, teacher);
        } else { // if teacher deselected
            activities.unassign(activity);
        }

    } else { // if create

        activity = new Activity();
        activity->setTitle(ui->title->text());
        activity->setDescription(ui->description->toPlainText());
        activity->setStartDate(ui->startDate->dateTime());
        activity->setEndDate(ui->endDate->dateTime());
        activity->setFee(ui->fee->value());

        // if teacher selected
        if (index) {
            teacher = teachers.getElementAt(index - 1);
            activities.assign(activity, teacher);
        } else {
            activities.insert(activity);
        }
    }

    box->show();
}

