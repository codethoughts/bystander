#include <QtGui>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>

#include "login.h"
#include "userform.h"
#include "activityform.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadTeacherViewList();
    loadStaffViewList();
    loadActivityViewList();

    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    box.setDefaultButton(QMessageBox::No);


    loadHTML();

}

void MainWindow::loadHTML()
{
    QFile ua_file("unassigned_activity.html");
    QTextStream ua_in(&ua_file);

    if (ua_file.open(QIODevice::ReadOnly))
        unassigned_activity_html = ua_in.readAll();


    QFile aa_file("assigned_activity.html");
    QTextStream  aa_in(&aa_file);
    if (aa_file.open(QIODevice::ReadOnly))
        assigned_activity_html = aa_in.readAll();


    QFile at_file("assigned_teacher.html");
    QTextStream  at_in(&at_file);
    if (at_file.open(QIODevice::ReadOnly))
        assigned_teacher_html = at_in.readAll();

    QFile ut_file("unassigned_teacher.html");
    QTextStream  ut_in(&ut_file);
    if (ut_file.open(QIODevice::ReadOnly))
        unassigned_teacher_html = ut_in.readAll();

    QFile s_file("staff.html");
    QTextStream s_in(&s_file);
    if (s_file.open(QIODevice::ReadOnly))
        staff_html = s_in.readAll();

}

void MainWindow::userSelectedItem(const QModelIndex& selected, const QModelIndex& deselected)
{
    ui->editButton->setDisabled(false);
    ui->deleteButton->setDisabled(false);

    int index = selected.row();

    const Teacher* self = &teachers.data().at(index);
    Activity* activity = activities.findActivityByInnerID(self);

    QString name = self->getName();
    QString email = self->getEmail();
    QString usr = self->getUsername();

    QString html;

    if (activity) {
        html = assigned_teacher_html;

        QString activity_id =
                QString().number(self->getActivityID());
        QString title = activity->getTitle();
        QString start = activity->getStartDate().toString("dd/MM/yyyy hh:mm");;
        QString end = activity->getEndDate().toString("dd/MM/yyyy hh:mm");;

        html.replace(QRegularExpression("{username}"), usr);
        html.replace(QRegularExpression("{teacher_name}"), name);
        html.replace(QRegularExpression("{teacher_email}"),email);
        html.replace(QRegularExpression("{activity_id}"), activity_id);
        html.replace(QRegularExpression("{title}"), title);
        html.replace(QRegularExpression("{start}"), start);
        html.replace(QRegularExpression("{end}"), end);
    } else {
        html = unassigned_teacher_html;

        html.replace(QRegularExpression("{username}"), usr);
        html.replace(QRegularExpression("{teacher_name}"), name);
        html.replace(QRegularExpression("{teacher_email}"),email);

    }

    ui->preview->setHtml(html);


}

void MainWindow::activitySelectedItem(const QModelIndex& selected, const QModelIndex& deselected)
{
    ui->editButton->setDisabled(false);
    ui->deleteButton->setDisabled(false);

    int index = selected.row();
    const Activity* self = activities.getActivityAt(index);
    Teacher* teacher = activities.getTeacher(self);

    QString id = QString().number(self->getID());
    QString title = self->getTitle();
    QString description = self->getDescription();
    QString duration = self->getEndDate() - self->getStartDate();
    QString start = self->getStartDate().toString("dd/MM/yyyy hh:mm");
    QString end = self->getEndDate().toString("dd/MM/yyyy hh:mm");
    QString left = self->getStartDate() - QDateTime().currentDateTime();
    QString teacher_usr = self->getTeacherUsr();
    QString fee = "RM " + QString().number(self->getFee());

    QString html;

    if (teacher) {
        html = assigned_activity_html;

        html.replace(QRegularExpression("\{title\}"), title);
        html.replace(QRegularExpression("\{activity_id\}"), id);
        html.replace(QRegularExpression("\{left\}"), left);
        html.replace(QRegularExpression("\{username\}"), teacher_usr);
        html.replace(QRegularExpression("\{teacher_name\}"), teacher->getName());
        html.replace(QRegularExpression("\{teacher_email\}"),teacher->getEmail());
        html.replace(QRegularExpression("\{description\}"),description);
        html.replace(QRegularExpression("\{start\}"), start);
        html.replace(QRegularExpression("\{end\}"), end);
        html.replace(QRegularExpression("\{duration\}"), duration);
        html.replace(QRegularExpression("\{fee\}"), fee);
    } else {
        html = unassigned_activity_html;

        html.replace(QRegularExpression("\{title\}"), title);
        html.replace(QRegularExpression("\{activity_id\}"), id);
        html.replace(QRegularExpression("\{left\}"), left);
        html.replace(QRegularExpression("\{description\}"),description);
        html.replace(QRegularExpression("\{start\}"), start);
        html.replace(QRegularExpression("\{end\}"), end);
        html.replace(QRegularExpression("\{duration\}"), duration);
        html.replace(QRegularExpression("\{fee\}"), fee);
    }

    ui->preview->setHtml(html);
}


void MainWindow::loadTeacherViewList(QVector<Teacher> _teachers)
{
    QStandardItemModel* teacher_model =
            new QStandardItemModel(this);
    QStandardItem* teacher_item;

    int i = 0;
    for (auto t : _teachers) {

        teacher_item = new QStandardItem(t.getUsername());

        teacher_model->setItem(i, teacher_item);
        i++;
    }

    ui->usersList->setModel(teacher_model);

    QItemSelectionModel* userSelection = ui->usersList->selectionModel();
    connect(userSelection, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,
            SLOT(userSelectedItem(QModelIndex,QModelIndex)));
}


void MainWindow::loadActivityViewList()
{
    QStandardItemModel* activity_model = new QStandardItemModel(this);
    QStandardItem* activity_item;

    int i = 0;
    for (auto a : activities.getActivities()) {

        activity_item = new QStandardItem(
                    QString().number(a.getID())
                    + "\t" + a.getTitle());

        activity_model->setItem(i, activity_item);
        i++;
    }

    ui->activitiesList->setModel(activity_model);


    QItemSelectionModel* activitySelection = ui->activitiesList->selectionModel();
    connect(activitySelection, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,
            SLOT(activitySelectedItem(QModelIndex,QModelIndex)));
}


void MainWindow::loadStaffViewList(QVector<Staff>)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createButton_clicked()
{
    int currentTab = ui->tabWidget->currentIndex();

    if (currentTab) // activities
    {
        ActivityForm* activity_form = new ActivityForm(this);
        activity_form->show();

    } else { // users
        UserForm *user_form = new UserForm(this);
        user_form->show();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int currentTab = ui->tabWidget->currentIndex();
    int row;
    if (currentTab)
    {
        row = ui->activitiesList->currentIndex().row();
        if (row >= 0) {

            if (activities.getActivityAt(row)->getTeacherUsr() != 0)
            {
                box.setInformativeText("The record is attached to teacher. "
                                       "Revoke and delete record?");
            } else {
                box.setText("Delete activity?\n");
            }
            int res = box.exec();

            switch(res) {
            case QMessageBox::Yes:

                ui->activitiesList->selectionModel()->reset();
                ui->activitiesList->model()->removeRow(row);
                ::activities.removeAt(row);

                break;
            }
        }
    } else {
        row = ui->usersList->currentIndex().row();

        if (row >= 0) {
            if (teachers.data().at(row).getActivityID())
            {
                box.setText("This teacher is assigned to activity.");
                box.setInformativeText("Unassign from the activity and delete user?");
            } else {
                box.setText("Delete user?\n");
            }

            int res = box.exec();

            switch(res) {
                case QMessageBox::Yes:

                row  = ui->usersList->selectionModel()->currentIndex().row();
                ui->usersList->selectionModel()->reset();
                ui->usersList->model()->removeRow(row);
                teachers.removeAt(row);

                break;
            }
        }
    }
}

void MainWindow::on_activityTypesComboBox_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_userTypesComboBox_currentIndexChanged(const QString &arg1)
{

}

void MainWindow::on_editButton_clicked()
{
    int currentTab = ui->tabWidget->currentIndex();
    int row;
    if (currentTab)
    {
        row = ui->activitiesList->currentIndex().row();
        if (row >= 0) {
            Activity* self =
                    activities.getActivityAt(row);

            ActivityForm* activity_form = new ActivityForm(this);
            activity_form->setActivity(self);
            activity_form->show();
        }
    } else {
        row = ui->usersList->currentIndex().row();
        if (row >= 0) {
            Teacher* teacher = teachers.getElementAt(row);
            UserForm *user_form = new UserForm(this);
            user_form->setTeacher(teacher);
            user_form->show();
        }
    }

    qDebug() << activities.getActivities(1);

}

void MainWindow::on_actionLogout_triggered()
{
    Login* login = new Login();
    login->show();
    this->setVisible(false);
    ui->actionLogout->setDisabled(true);
}

void MainWindow::on_actionRefresh_triggered()
{
    loadTeacherViewList();
    loadStaffViewList();
    loadActivityViewList();
}

void MainWindow::on_searchBox_returnPressed()
{
    QString text = ui->searchBox->text();

    if (!ui->tabWidget->currentIndex())
    {

        QRegularExpression re(".*"+ text + ".*");

        QVector<Teacher*> temp;
        for (Teacher& t : teachers.data()) {

            QRegularExpressionMatch m =
                    re.match(t.getEmail() + t.getName() + t.getUsername());

            if (m.hasMatch())
            {
                temp.push_back(&t);
                qDebug() << t.getUsername();
            }
        }

//        loadTeacherViewList(temp);

    } else {

    }
}


void MainWindow::on_searchBox_cursorPositionChanged(int arg1, int arg2)
{
    if ((arg1 == arg2) == 0 && ui->searchBox->text().isEmpty())
    {

    }
}
