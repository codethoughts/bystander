#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QtCore>

quint32 getUniqueID();

class Activity
{
private:
    quint32 id;
    QString teacher_usr;
    QString title;
    QString description;
    QDateTime startDate;
    QDateTime endDate;
    float fee;

public:
    Activity(
            QString title           =       0,
            QString description     =       0,
            QDateTime start_date    =       QDateTime().currentDateTime(),
            QDateTime end_date      =       QDateTime().currentDateTime().addDays(1),
            float fee               =       0.0,
            quint32 id              =       getUniqueID()
            );

    ~Activity();

    quint32 getID() const;
    void setID(quint32);

    QString getTeacherUsr() const;
    void setTeacherUsr(QString = 0);

    QString getTitle() const;
    void setTitle(QString);

    QString getDescription() const;
    void setDescription(QString);

    QDateTime getStartDate() const;
    void setStartDate(QDateTime);

    QDateTime getEndDate() const;
    void setEndDate(QDateTime);

    float getFee() const;
    void setFee(float);


    bool operator<(Activity* b)
    {
       return id < b->getID();
    }

    bool operator==(const Activity& operand)
    {
        return id == operand.getID();
    }

    bool operator==(const Activity* operand)
    {
        return id == operand->getID();
    }

    bool operator==(const quint32 id)
    {
        return this->id == id;
    }

    void operator= (const quint32 id)
    {
        this->id = id;
    }

    void operator<< (const quint32 id)
    {
        this->id = id;
    }

};


#endif // ACTIVITY_H
