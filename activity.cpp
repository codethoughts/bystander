#include <QDateTime>
#include <QString>

#include "activity.h"

#include "file_delegator.hpp"
#include "mapping.h"

#include "activityreference.h"

extern ActivityReference activities;

Activity::Activity (
        QString title,
        QString description,
        QDateTime start_date,
        QDateTime end_date,
        float fee,
        quint32 id)      :
                                title(title),
                                description(description),
                                startDate(start_date),
                                endDate(end_date),
                                fee(fee),
                                id(id)
{ }

Activity::~Activity()
{ }

quint32 Activity::getID() const
{
    return id;
}
void Activity::setID(quint32 id)
{
    this->id = id;
}
QString Activity::getTeacherUsr() const
{
    return teacher_usr;
}
void Activity::setTeacherUsr(QString usr)
{
    teacher_usr = usr;
}
QString Activity::getTitle() const
{
    return title;
}
void Activity::setTitle(QString title)
{
    this->title = title;
}
QString Activity::getDescription() const
{
    return description;
}
void Activity::setDescription(QString description)
{
    this->description = description;
}
QDateTime Activity::getStartDate() const
{
    return startDate;
}
void Activity::setStartDate(QDateTime start_date)
{
    startDate = start_date;
}
QDateTime Activity::getEndDate() const
{
    return endDate;
}
void Activity::setEndDate(QDateTime end_date)
{
    endDate = end_date;
}
float Activity::getFee() const
{
    return fee;
}
void Activity::setFee(float fee)
{
    this->fee = fee;
}

quint32 getUniqueID() {

    quint32 id = rand() % UINT32_MAX + 1;

//    auto it = find_if(activities.getActivities().begin(),
//                  activities.getActivities().end(),
//                  [&id] (Activity* t) { return *t == id; });



//    bool hasSame = (it != activities.getActivities().end());

//    if (hasSame) {
//        do {

//            id = rand() % UINT32_MAX;
//            it = find_if(activities.getActivities().begin(),
//                     activities.getActivities().end(),
//                     [&id] (Activity* t) { return *t == id; });

//            hasSame = (it != activities.getActivities().end());

//        } while (!hasSame);

//    } else {
//        qDebug() << "ID:" << id << "assigned";
//    }

    return id;
}
