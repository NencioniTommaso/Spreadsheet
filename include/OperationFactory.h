//
// Created by nenci on 19/04/2025.
//

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

#include "OperationId.h"
#include "Operation.h"
#include "MaxOperation.h"
#include "MinOperation.h"
#include "SumOperation.h"

class OperationFactory {
public:
    static std::unique_ptr<Operation> createOperation(OperationId id) {
        switch (id) {
            case OperationId::Max:
                return std::unique_ptr<MaxOperation>(new MaxOperation());
            case OperationId::Min:
                return std::unique_ptr<MinOperation>(new MinOperation());
            case OperationId::Sum:
                return std::unique_ptr<SumOperation>(new SumOperation());
            case OperationId::Mean:
                return std::unique_ptr<SumOperation>(new SumOperation(true));
            default:
                return nullptr;         //tiene conto anche del caso NoOp
        }
    }
};

#endif //OPERATIONFACTORY_H
