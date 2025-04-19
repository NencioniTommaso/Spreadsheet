//
// Created by nenci on 19/04/2025.
//

#ifndef OPERATION_H
#define OPERATION_H

#include <list>
#include "Cell.h"

class Cell;

class Operation {
public:
    virtual double compute(const std::list<Cell*>& cells) const = 0;
    virtual ~Operation() = default;
};

#endif //OPERATION_H
