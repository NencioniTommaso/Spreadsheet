#ifndef SPREADSHEET_SUBJECT_H
#define SPREADSHEET_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

#endif