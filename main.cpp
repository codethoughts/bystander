#include <QApplication>
#include <algorithm>
#include <map>

#include "login.h"
#include "mainwindow.h"

#include "teacher.h"
#include "staff.h"

#include "file_delegator.hpp"

#include "ActivityReference.h"

using namespace std;


struct StaticBlock {
    StaticBlock(){
        srand((unsigned)time(NULL));
    }
};


static StaticBlock staticBlock;


Delegator<Staff> staffs;
Delegator <Teacher> teachers;
ActivityReference activities(true);


static QString getRandomString();
void TEST_1();


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    Login login;
    login.show();

//    TEST_1();


//    MainWindow m;
//    m.show();

    return a.exec();
}

void TEST_1()
{
    /*
     * 1.0 TEST 1,2,3,4,5
     */
    Activity* a;
    Teacher* t;

    for(quint32 i = 1; i<= 100; ++i)
    {
        a = new Activity(getRandomString(),getRandomString());
        t = new Teacher(getRandomString(),getRandomString());

        a->setID(i);
        a->setFee(i * (rand() % 50));

        t->setUsername(getRandomString());
        t->setName(getRandomString());
        t->setEmail(getRandomString());

        if (i%2)
        {
            activities.assign(a,t);
        } else {
            activities.insert(a);
            teachers.insert(t);
        }
    }
    /*
     * END TEST
     */

    qCritical() << "OUT OF FUNCTION";
}



static QString getRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}
