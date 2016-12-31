#include <QtGui>
#include <QDebug>
#include <QThread>
#include <QTime>

#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

class InvalidLogin : public QThread
{
    QLabel* indicator;
public:
    InvalidLogin(QLabel* indicator)
    {
        this->indicator = &(*indicator);
    }

    void run()
    {
        qDebug() << indicator->text();
        indicator->setVisible(true);
        QTime fix = QTime().currentTime().addSecs(3);
        while(QTime().currentTime() != fix);
        indicator->setVisible(false);
    }
};

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setFixedSize(window.size());
    ui->indicator->setVisible(false);
}

Login::~Login()
{
    delete ui;
}


void Login::on_label_linkActivated(const QString &link)
{

    qDebug() << "Do user authentification";

//     if user is staff


    for (auto t : teachers.data())
    {
        if (t.getUsername() == ui->username->text()
                && t.getPassword() == ui->password->text())
        {
            UserForm* form = new UserForm();
            form->setTeacher(&t);
            form->setVisible(true);
            setVisible(false);
            destroy();
            close();
            return;
        }
    }

    if (ui->username->text() == "admin"
            && ui->password->text() == "123")
    {
        window.setVisible(true);
        setVisible(false);
        destroy();
        close();
        return;
    }

   (new  InvalidLogin(ui->indicator))->start();
}
