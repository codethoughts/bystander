#ifndef DELEGATOR_H
#define DELEGATOR_H

#include <QTypeInfo>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <string>
#include <QtCore>
#include <QRegularExpression>
#include <algorithm>

#include "staff.h"
#include "activity.h"
#include "teacher.h"

#include "mapping.h"

using namespace std;


#define s(T) typeid(T).name()


template <class T>
class Delegator
{
protected:
    QVector<T> _data;
    bool _reliable_mode;
    QString _FILENAME;
    bool isExist(T* t);
    void push(T* t);
    void load();
    void save();

public:
    /*
     * flag false in reliable_mode
     * insert data faster
     */

    Delegator<T>(bool = false);
    ~Delegator();

    T* getElement(const quint32 id);
    T* getElement(const QString username);

    T* getElementAt(int index);
    QVector<T> data();

    void insert(T* t);
    void remove(T* t);

    void removeAt(int index);

    void mode(bool m);
};


template <class T>
Delegator<T>::Delegator(bool mode)   :   _reliable_mode(mode)
{
    QString CLASS_NAME =
            QString().fromStdString(std::string(s(T),strlen(s(T))));

    QString FILENAME =
            CLASS_NAME.remove(QRegularExpression("\\d")) + ".bin";


    _FILENAME = FILENAME;

    load();

}

template <class T>
Delegator<T>::~Delegator()
{
    save();
    _data.clear();
}


template <class T>
T* Delegator<T>::getElementAt(int index)
{

    return &_data[index];
}


template <class T>
void Delegator<T>::save()
{
    QFile file(_FILENAME);

    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << _data;
        qDebug() << "\nSAVED " << _FILENAME
                 << ":" << _data.size() << "\n";
        out.device()->close();
    } else {
        qCritical() << "ERROR WRITE :" << _FILENAME;
    }

    file.flush();
    file.close();
}


template <class T>
void Delegator<T>::load()
{
    _data.clear();
    QFile file(_FILENAME);

    if (!file.exists()) {
        qDebug() << "\nNOT EXIST"
                 << _FILENAME << "\n";
    }
    else if (file.size() < sizeof(vector<T>))
    {
        qDebug() << "\nEMPTY" << _FILENAME << "\n";
    }
    else if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> _data;

        qDebug() << "\nDATA :" << _FILENAME
                 << ":" << _data.size()
                 << "\nSTART";
        for (auto t : _data)
        {
            qDebug() << t;
        }
        qDebug() << "END\n";

        in.device()->close();

    } else {
        qCritical() << "ERROR READ" << _FILENAME;
    }
    file.flush();
    file.close();
}

template <class T>
QVector<T> Delegator<T>::data()
{
    return _data;
}

template <class T>
T* Delegator<T>::getElement(const quint32 id)
{
    auto it =
            find_if(_data.begin(),
                    _data.end(),
                    [&id](T& t)
                    {
                        return t == id;
                    });

    if (it != _data.end())
    {
        return it;
    } else {
        return 0;
    }
}

template <class T>
T* Delegator<T>::getElement(const QString usr)
{
    auto it =
            find_if(_data.begin(),
                    _data.end(),
                    [&usr](T& t)
                    {
                        return t == usr;
                    });

    if (it != _data.end())
    {
        return it;
    } else {
        return 0;
    }
}

template <class T>
bool Delegator<T>::isExist(T* t)
{
    auto i = find_if(_data.begin(),
                     _data.end(),
                     [&t](T& o)
                     {
                         return o == *t;
                     });

    if (i != _data.end()) // aka object found
    {
        return true;
    } else {
        qDebug() << "\nNOT FOUND :" << _FILENAME
                 << "\n";

        return false;
    }
}

template <class T>
void Delegator<T>::insert(T* t)
{
    if (!_data.empty()) // data exist
    {
        auto i = find_if(_data.begin(),
                         _data.end(),
                         [&t] (T& o)
                         {
                             return o == *t;
                         });

        if (i != _data.end())
        {
            // aka object found change ref
            qDebug() << "\nINSERT OPERATION : "
                       "REFERENCE UPDATED : "
                    << _FILENAME << "\n";

            i = t;
        }
        else // not found
            push(*&t);

    } else // data not exist
    {
        push(*&t);
    }
}



template <class T>
void Delegator<T>::push(T* t)
{
    _data.push_back(*t);
    qDebug().nospace()
            << "\nINSERT OPERATION : "
            << _FILENAME;
    if (_reliable_mode) save();
}

template <class T>
void Delegator<T>::remove(T* t)
{
    if (isExist(t))
    {
        qDebug().nospace()
                << "\nREMOVE OPERATION : " << _FILENAME;

        _data.erase(std::remove(
                        _data.begin(),
                        _data.end(),
                        t),
                    _data.end());

        if (_reliable_mode) save();
    }
}

template <class T>
void Delegator<T>::removeAt(int index)
{
    _data.removeAt(index);
}

template<class T>
void Delegator<T>::mode(bool m)
{
    _reliable_mode = m;
}

#endif // Delegator_H
