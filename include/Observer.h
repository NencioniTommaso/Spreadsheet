#ifndef SPREADSHEET_OBSERVER_H
#define SPREADSHEET_OBSERVER_H

class Subject;

class Observer{
public:
    virtual void update() = 0;
    virtual void attach(Subject* s) = 0;
    virtual void detach(Subject* s) = 0;
    virtual ~Observer() {}
};

#endif