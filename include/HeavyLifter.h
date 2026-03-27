#ifndef HEAVYLIFTER_H
#define HEAVYLIFTER_H

#include "Vessel.h"
#include <fstream>
#include <string>

class HeavyLifter : public Vessel {
public:
    HeavyLifter(int id, const std::string& name);
    HeavyLifter(int id, const std::string& name, int maxCapacity);

    double  calculateFuel(int distance)         const override;
    Vessel* clone()                             const override;
    void    display()                           const override;
    void    writeReport(std::ofstream& out)     const override;
};

#endif // HEAVYLIFTER_H
