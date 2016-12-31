#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "mainwindow.h"
#include "userform.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    MainWindow window;
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:

    void on_label_linkActivated(const QString &link);

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
