#include <QTime>
#include <QDateTime>
#include <QString>
#include <sstream>
#include <string>

#include "Activity.h"
#include "Staff.h"
#include "Teacher.h"

#include "mapping.h"

using namespace std;

QTime &operator-(const QTime& time1, const QTime& time2)
{
    QTime diff;

    unsigned char h =
            abs(time1.hour() - time2.hour());
    unsigned char m =
            abs(time1.minute() - time2.minute());

    diff = QTime(h,m);

    return diff;
}

QString operator-(const QDateTime& date1, const QDateTime& date2)
{
    unsigned short cal_y =
            abs(date1.date().year() - date2.date().year());;
    unsigned char cal_m =
            abs(date1.date().month() - date2.date().month());
    unsigned char cal_d =
            abs(date1.date().day() - date2.date().day());
    QTime time =
            date1.time() - date2.time();

    stringstream result;

    result << (!cal_y ? "" : to_string(cal_y) + " years, ")
           << (!cal_m ? "" : to_string(cal_m) + " months, ")
           << (!cal_d ? "" : to_string(cal_d) + " day ")
           << (!time.hour() ? "" : to_string(time.hour()) + " hours ")
           << (!time.minute() ? "" : to_string(time.minute()) + " minutes");

    QString str_result = QString().fromStdString(result.str());

    result.flush();
    result.clear();

    return str_result;
}


QDebug operator<<(QDebug os, const Staff& self)
{
    os << "{\n"
          "    username:" << self.getUsername() << "\n"
          "    password:" << self.getPassword() << "\n"
          "    name:" << self.getName() << "\n"
          "}";

    return os;
}

//

ostream& operator<<(ostream& os, const QString& s)
{
    return os << s.toStdString();
}

ostream& operator<<(ostream& os, const QDateTime& s)
{
    return os << s.toString();
}


ostream& operator<<(ostream& os, const Teacher& self)
{
    os << "{\n"
          "    activity:" << self.getActivityID() << "\n"
          "    username:" << self.getUsername() << "\n"
          "    password:" << self.getPassword() << "\n"
          "    name:" << self.getName() << "\n"
          "    email:" << self.getEmail() << "\n"
          "}";

    return os;
}

ostream& operator<<(ostream& os, const Activity& self)
{
    os << "{\n"
          "    id:" << self.getID() << "\n"
          "    teacher:" << self.getTeacherUsr() << "\n"
          "    title:" << self.getTitle() << "\n"
          "    description:" << self.getDescription() << "\n"
          "    fee:" << self.getFee() << "\n"
          "    start:" << self.getStartDate() << "\n"
          "    end:" << self.getEndDate() << "\n"
          "}";

    return os;
}

//
QDebug operator<<(QDebug os, const Teacher& self)
{
    os << "{\n"
          "    activity:" << self.getActivityID() << "\n"
          "    username:" << self.getUsername() << "\n"
          "    password:" << self.getPassword() << "\n"
          "    name:" << self.getName() << "\n"
          "    email:" << self.getEmail() << "\n"
          "}";

    return os;
}

QDebug operator<<(QDebug os, const Activity& self)
{
    os << "{\n"
          "    id:" << self.getID() << "\n"
          "    teacher:" << self.getTeacherUsr() << "\n"
          "    title:" << self.getTitle() << "\n"
          "    description:" << self.getDescription() << "\n"
          "    fee:" << self.getFee() << "\n"
          "    start:" << self.getStartDate() << "\n"
          "    end:" << self.getEndDate() << "\n"
          "}";

    return os;
}

/*
 * Activity
 */
QDataStream& operator<< (QDataStream& out, const Activity& self)
{
    out << self.getID()
        << self.getTeacherUsr()
        << self.getTitle()
        << self.getDescription()
        << self.getStartDate()
        << self.getEndDate()
        << self.getFee();

    return out;
}
QDataStream& operator>> (QDataStream& in, Activity& self)
{
    quint32     id;
    QString     teacher_usr;
    QString     title;
    QString     description;
    QDateTime   start_date;
    QDateTime   end_date;
    float       fee;

    in >> id
       >> teacher_usr
       >> title
       >> description
       >> start_date
       >> end_date
       >> fee;

    self = Activity(title,description,start_date,end_date,fee,id);
    self.setTeacherUsr(teacher_usr);

    return in;
}

/*
 * Teacher
 */
QDataStream & operator<< (QDataStream& out, const Teacher& self)
{
    out << self.getActivityID()
        << self.getUsername()
        << self.getPassword()
        << self.getName()
        << self.getEmail();

    return out;
}
QDataStream& operator>> (QDataStream& in, Teacher& self)
{
    quint32     activity_id;
    QString     username;
    QString     password;
    QString     name;
    QString     email;

    in >> activity_id
       >> username
       >> password
       >> name
       >> email;

    self = Teacher(username,
                       password,
                       email,
                       name,
                       activity_id);

    return in;
}

/*
 * Staff
 */
QDataStream& operator<< (QDataStream& out, const Staff& self)
{
    out << self.getUsername()
        << self.getPassword()
        << self.getName();

    return out;
}
QDataStream& operator>> (QDataStream& in, Staff& self)
{
    QString     username;
    QString     password;
    QString     name;

    in >> username
       >> password
       >> name;

    self = Staff(username, password, name);

    return in;
}
