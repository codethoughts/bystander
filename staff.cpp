#include <QString>

#include "staff.h"

Staff::Staff(QString username,
             QString password,
             QString name)
{
    this->username = username;
    this->password = password;
    this->name = name;
}
