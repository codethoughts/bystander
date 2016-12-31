#include <QString>

#include "teacher.h"

Teacher::Teacher(
        QString username,
        QString password,
        QString email,
        QString name,
        quint32 activity_id)    :   email(email),
                                    activity_id(activity_id)
{
    this->username      =     username;
    this->password      =     password;
    this->name          =     name;
}

quint32 Teacher::getActivityID() const
{
    return activity_id;
}
void Teacher::setActivityID(quint32 id)
{
    activity_id = id;
}

QString Teacher::getEmail() const
{
    return email;
}
void Teacher::setEmail(QString email)
{
    this->email = email;
}

