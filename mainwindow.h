#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndexList>
#include <QItemSelection>
#include <QMessageBox>

#include "staff.h"
#include "activity.h"
#include "teacher.h"

#include "file_delegator.hpp"
#include "activityreference.h"


extern ActivityReference activities;
extern Delegator<Teacher> teachers;
extern Delegator<Staff> staffs;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QString unassigned_activity_html;
    QString assigned_activity_html;
    QString unassigned_teacher_html;
    QString assigned_teacher_html;
    QString staff_html;

    ~MainWindow();

private slots:

    void userSelectedItem(const QModelIndex&, const QModelIndex&);
    void activitySelectedItem(const QModelIndex&, const QModelIndex&);


    void on_createButton_clicked();
    void on_deleteButton_clicked();
    void on_activityTypesComboBox_currentIndexChanged(const QString &arg1);
    void on_userTypesComboBox_currentIndexChanged(const QString &arg1);
    void on_editButton_clicked();

    void on_actionLogout_triggered();
    void on_actionRefresh_triggered();

    void on_searchBox_returnPressed();
    void on_searchBox_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;

    void loadTeacherViewList(QVector<Teacher> = teachers.data());
    void loadStaffViewList(QVector<Staff> = staffs.data());
    void loadActivityViewList();
    void loadHTML();

    QMessageBox box;
};

#endif // MAINWINDOW_H
