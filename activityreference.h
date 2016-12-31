#ifndef ACTIVITYREFERENCE_H
#define ACTIVITYREFERENCE_H

#include <map>
#include <iostream>
#include <algorithm>

#include "file_delegator.hpp"
#include "teacher.h"
#include "activity.h"

using namespace std;

extern Delegator<Teacher> teachers;

class ActivityReference
{
private:
    Delegator<Activity> _activities;
    map <Activity*, Teacher*> _links;
    //find elements by key
    Teacher* findTeacherByInnerID(const Activity&);
    // map all elements by reference
    void mapLinks();
    // links to objects
    void bind(Activity*, Teacher*);

public:
    // load data from disk
    // set deligator mode
    ActivityReference(bool mode = false);
    // save changes on disk
    ~ActivityReference();

    // insert activity without binding
    void insert(Activity* _new);
    // remove existing activity
    void remove(Activity* _old);
    void removeAt(int index);

    // insert reference (assign activity to teacher)
    void assign(Activity* key, Teacher* value);

    // remove reference (revoke activity from teacher)
    void unassign(Activity* key);
    void unassign(Teacher* value);

    // return links by status
    map<Activity*, Teacher*> *getLinks();
    QVector<Activity> getActivities(int status = -1);

    //find elements by value
    Activity* findActivityByInnerID(const Teacher*);

    int getSize();

    // return teacher by activity
    Teacher* getTeacher(const Activity* activity);
    Activity* getActivityAt(int index);

    bool isBinded(Activity*);
    bool isBinded(Teacher*);
};

#endif // ActivityReference_H
