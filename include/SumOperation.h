//
// Created by nenci on 19/04/2025.
//

#ifndef SUMOPERATION_H
#define SUMOPERATION_H

class SumOperation : public Operation {
public:
    SumOperation(bool calculateMean = false) : calculateMean(calculateMean) {}

    double compute(const std::list<Cell*>& cells) const override {
        double s = 0;
        int validSize = 0;
        for (auto c : cells) {
            try {
                if (!c->getValue().empty()) { // Salta le celle vuote
                    s += std::stod(c->getValue());
                    validSize++;
                }
            } catch (const std::invalid_argument&) {
                // Ignora i valori non validi
            } catch (const std::out_of_range&) {
                // Ignora valori fuori dall'intervallo
            }
        }

        if (calculateMean)
            s /= validSize;
        return s;
    }
private:
    bool calculateMean;
};

#endif //SUMOPERATION_H
