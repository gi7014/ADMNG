#ifndef CPERSON_H
#define CPERSON_H

#include <QString>

struct CPerson{
    QString name;
    QString address;
    QString Phone_number;
    QString Postal_code;
    struct CPerson *next=NULL;
};

#endif // CPERSON_H
