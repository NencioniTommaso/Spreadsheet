//
// Created by nenci on 19/04/2025.
//

#ifndef MINOPERATION_H
#define MINOPERATION_H

class MinOperation : public Operation {
public:
    double compute(const std::list<Cell*>& cells) const override {
        double v, min = std::numeric_limits<double>::infinity();
        for (auto c:cells) {
            try {
                if (!c->getValue().empty()) {
                    if (std::stod(c->getValue()) < min)
                        min = std::stod(c->getValue());
                }
            } catch (const std::invalid_argument&) {
                continue;
            } catch (const std::out_of_range&) {
                continue;
            }
        }
        return min;
    }
};

#endif //MINOPERATION_H
