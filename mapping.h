#ifndef OVERLOADINGS
#define OVERLOADINGS

#include <QDataStream>
#include <sstream>
#include <iostream>

#include "activity.h"
#include "teacher.h"
#include "staff.h"

using namespace std;

bool operator==(const Teacher& t, quint32 id);

QTime &operator-(const QTime& time1, const QTime& time2);

QString operator-(const QDateTime& date1, const QDateTime& date2);

QDebug operator<<(QDebug os, const Staff& self);

//
ostream& operator<<(ostream& os, const QString& s);

ostream& operator<<(ostream& os, const QDateTime& s);


ostream& operator<<(ostream& os, const Teacher& self);

ostream& operator<<(ostream& os, const Activity& self);

//
QDebug operator<<(QDebug os, const Teacher& self);

QDebug operator<<(QDebug os, const Activity& self);

/*
 * Activity
 */
QDataStream& operator<< (QDataStream& out, const Activity& self);

QDataStream& operator>> (QDataStream& in, Activity& self);

/*
 * Teacher
 */
QDataStream & operator<< (QDataStream& out, const Teacher& self);

QDataStream& operator>> (QDataStream& in, Teacher& self);

/*
 * Staff
 */
QDataStream& operator<< (QDataStream& out, const Staff& self);

QDataStream& operator>> (QDataStream& in, Staff& self);

#endif // OVERLOADINGS

