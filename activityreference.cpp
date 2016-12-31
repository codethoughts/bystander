#include <QVector>

#include "activity.h"
#include "teacher.h"
#include "staff.h"

#include "file_delegator.hpp"
#include "mapping.h"

#include "activityreference.h"


extern Delegator<Teacher> teachers;

ActivityReference::ActivityReference(bool mode)
{
    _activities.mode(mode);
    mapLinks();
}

ActivityReference::~ActivityReference()
{ }

Activity* ActivityReference::getActivityAt(int index)
{
    return _activities.getElementAt(index);
}

QVector<Activity> ActivityReference::getActivities(int status)
{
    QVector<Activity> temp;

    switch (status) {
    case 1:

        qDebug() << "ASSIGNED REFERENCES"
                 << "\nSTART";

        for (auto key : _activities.data())
        {
            Teacher* value = findTeacherByInnerID(key);

            // set objects references
            if (value) {
                qDebug().nospace()
                        << "[\n"
                        << key
                        << "\n"
                        << value
                        << "\n]";

                temp.push_back(key);
            }
        }
        qDebug() << "END\n";
        break;
    case 0:
        for (auto i : _activities.data())
        {
            if (!findTeacherByInnerID(i))
            {
                temp.push_back(i);
            }
        }
        break;
    default:
        for (auto i : _activities.data())
        {
            temp.push_back(i);
        }
        break;
    }

    return temp;
}

bool ActivityReference::isBinded(Activity* key)
{
    auto i = _links.find(key);
    return i != _links.end() ? true : false;
}

bool ActivityReference::isBinded(Teacher* value)
{
    for (auto i : _links)
    {
        if (i.second == value) return true;
    }

    return false;
}

void ActivityReference::insert(Activity* _new)
{
    _activities.insert(_new);
}

void ActivityReference::remove(Activity* _old)
{
    Teacher* teacher = findTeacherByInnerID(*_old);

    unassign(_old);

    _activities.remove(_old);
}

void ActivityReference::removeAt(int index)
{
    Activity self = _activities.data().at(index);
    remove(&self);
}

void ActivityReference::bind(Activity* key, Teacher* value)
{
    // revoke from existing activity
    unassign(key);
    unassign(value);

    // assign to each other
    key->setTeacherUsr(value->getUsername());
    value->setActivityID(key->getID());
}

void ActivityReference::assign(Activity* key, Teacher* value)
{
    // bind & insert record if id is not 0
    if (key->getID()) {
        // provide redundency security
        bind(key, value);

        // insert to delegator
        _activities.insert(key);
    }

    if (value->getUsername() != 0) {

        teachers.insert(value);

    }



    //update references
    mapLinks();
}

void ActivityReference::unassign(Teacher* value)
{
    Activity* key;
    key = findActivityByInnerID(value);
    value->setActivityID();

    // unassign from activity
    if (key)
    {
        key->setTeacherUsr();
        qDebug() << "\nREFERENCE REMOVED\n";

    } else {
        qDebug() << "\nREFERENCE KEY NOT FOUND\n";
    }

    //update references
    mapLinks();
}

void ActivityReference::unassign(Activity* key)
{
    Teacher* value = findTeacherByInnerID(*key);
    key->setTeacherUsr();

    // unassign from teacher
    if (value)
    {
        value->setActivityID();
        qDebug() << "\nREFERENCE REMOVED\n";

    } else {
        qDebug() << "\nREFERENCE VALUE NOT FOUND\n";
    }

    //update references
    mapLinks();
}

int ActivityReference::getSize()
{
    return _links.size();
}

Teacher* ActivityReference::getTeacher(const Activity* key)
{
    return findTeacherByInnerID(*key);
}

Teacher* ActivityReference::findTeacherByInnerID(const Activity& key)
{
    // find assigned teacher
    return teachers.getElement(key.getTeacherUsr());
}

Activity* ActivityReference::findActivityByInnerID(const Teacher* key)
{
        return _activities.getElement(key->getActivityID());
}

void ActivityReference::mapLinks()
{
    _links.clear();

    if (_activities.data().empty())
    {
        qDebug() << "\nNO ACTIVITIES\n";
        return;

        qDebug() << "\nLINK REFERENCES REFRESHED\n";

        for (auto key : _activities.data())
        {
            Teacher* value = findTeacherByInnerID(key);

            // set objects references
            if (value) _links[&key] = value;
        }

        qDebug() << "END\n";
    }
}

map<Activity*, Teacher*>
*ActivityReference::getLinks()
{
    //update references
    mapLinks();
    return &_links;
}
