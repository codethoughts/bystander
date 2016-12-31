#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H


#include <QTypeInfo>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <string>
#include <QtCore>

#include <overloadings.h>

using namespace std;

#define s(T) typeid(T).name()

template <class T>
class Serializable
{
protected:
    QVector<T> _data;
    const QString filename = 
            QString().fromStdString(
                    std::string(s(T),
                    strlen(s(T))))
                        .replace(QRegExp("\\d"),"")
            + ".bin";
public:

    T* getElement(quint32 id);
    QVector<T>& data();

    void insert(T& t);
    void remove(const T& t);
    void load();
    void save();
    void close();
};

template <class T>
void Serializable<T>::close()
{
    save();
}

template <class T>
void Serializable<T>::save()
{
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << _data;
        qDebug() << "\nData saved in " << filename << "\n";
    } else {
        qCritical() << "ERROR : FILE WRITE :" << filename;
    }

    file.flush();
    file.close();
}

template <class T>
void Serializable<T>::load()
{
    QFile file(filename);

    if (!file.exists() || !file.size())
    {
        qDebug() << "FILE" << filename << "NOT EXIST OR EMPTY";
    }
    else if (file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        in >> _data;
        qDebug() << "\nData loaded from " << filename << "\n";

    } else {
        qCritical() << "ERROR : FILE READ :" << filename;
    }
    file.flush();
    file.close();
}

template <class T>
QVector<T>& Serializable<T>::data()
{
    return _data;
}

template <class T>
T* Serializable<T>::getElement(quint32 id)
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
        return &*it;
    } else {
        qDebug() << "not found : nullptr";
        return nullptr;
    }
}

template <class T>
bool Serializable<T>::insert(T& t)
{
    if (!_data.empty())
    {
        auto i = find_if(_data.begin(),
                         _data.end(),
                         [&t](const T& o)
                         {
                             return t == o;
                         });

        if (i == _data.end())
        {
            _data.push_back(t);
        } else {
            qDebug() << "Entity already exists";
            return false;
        }
    } else {
        _data.push_back(t);
        return true;
    }

    save();
    qDebug() << "Entity was successfully inserted and saved";
}

template <class T>
void Serializable<T>::remove(const T& t)
{
    _data.erase(std::remove(_data.begin(),
                            _data.end(),
                            t),
                _data.end());

    save();
}

#endif // SERIALIZABLE_H
