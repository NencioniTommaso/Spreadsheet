//
// Created by nenci on 19/04/2025.
//

#ifndef MAXOPERATION_H
#define MAXOPERATION_H

#include "Operation.h"
#include <limits>

class MaxOperation : public Operation {
public:
    double compute(const std::list<Cell*>& cells) const override {
        double v, max = -std::numeric_limits<double>::infinity();
        for (auto c:cells) {
            try {
                if (!c->getValue().empty()) {
                    if (std::stod(c->getValue()) > max)
                        max = std::stod(c->getValue());
                }
            } catch (const std::invalid_argument&) {
                continue;
            } catch (const std::out_of_range&) {
                continue;
            }
        }
        return max;
    }
};

#endif //MAXOPERATION_H
