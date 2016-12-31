#ifndef EMPLOYEE
#define EMPLOYEE

#include <QtCore>

using namespace std;


class Employee
{
protected:
    QString username;
    QString password;
    QString name;

public:
    virtual ~Employee()
    { }

    void setUsername(QString  usr)
    {
        username = usr;
    }
    QString  getUsername() const
    {
        return username;
    }
    void setPassword(QString  pwd)
    {
        password = pwd;
    }
    QString  getPassword() const
    {
        return password;
    }
    QString  getName() const
    {
        return name;
    }
    void setName(QString  name)
    {
        this->name = name;
    }

    void operator= (const QString username)
    {
        this->username = username;
    }

    void operator<< (const QString username)
    {
        this->username = username;
    }

    bool operator== (const QString username)
    {
        return this->username == username;
    }
};

#endif // EMPLOYEE_H


