#ifndef TEACHER_H
#define TEACHER_H

#include <QtCore>
#include <QDataStream>

#include "employee.h"

class Teacher : public Employee
{
private:
    QString email;
    quint32 activity_id;
public:
    Teacher(
            QString username        =       0,
            QString password        =       0,
            QString email           =       0,
            QString name            =       0,
            quint32 activity_id     =       0
            );


    quint32 getActivityID() const;
    void setActivityID(quint32 = 0);

    QString getEmail() const;
    void setEmail(QString);

    bool operator== (const Teacher& t)
    {
        return username == t.getUsername();
    }

    bool operator== (const QString username)
    {
        return this->username == username;
    }

};

#endif // TEACHER_H
