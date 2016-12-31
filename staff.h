#ifndef STAFF_H
#define STAFF_H

#include <QtCore>

#include "Employee.h"

class Staff : public Employee
{
public:
    Staff(
          QString username     =       0,
          QString password     =       0,
          QString name         =       0
          );

    bool operator==(Staff* operand)
    {
        return username == operand->getUsername();
    }
//    bool operator==(quint32 id)
//    {
//        return this->id == id;
//    }
};

#endif // STAFF_H
