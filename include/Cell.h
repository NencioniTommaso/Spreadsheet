#ifndef SPREADSHEET_CELL_H
#define SPREADSHEET_CELL_H

#include <wx/wx.h>
#include <list>
#include <string>
#include <memory>
#include <limits>
#include "Subject.h"
#include "Observer.h"
#include "OperationId.h"
#include "Operation.h"

class Cell : public Subject, public Observer {
public:
    Cell() : operation(nullptr), operationId(OperationId::NoOp) { value = ""; }
    ~Cell();

    void setValue(const std::string& v);

    const std::string &getValue() const {return value;}
    void setOperation(OperationId id);
    OperationId getOperationId() const {return operationId;}

    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;
    void notify() override;

    void update() override;
    void attach(Subject* s) override;
    void detach(Subject* s) override;

    void clearWatchedCells();
    void calcValue();

private:
    std::list<Observer*> observers;
    std::list<Cell*> cells;
    std::unique_ptr<Operation> operation;
    OperationId operationId;
    std::string value;

    int cellsSize() const;
    bool checkValidity(const std::string& str) const;
};


#endif