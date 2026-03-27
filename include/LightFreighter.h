#ifndef LIGHTFREIGHTER_H
#define LIGHTFREIGHTER_H

#include "Vessel.h"
#include <fstream>
#include <string>

class LightFreighter : public Vessel {
public:
    LightFreighter(int id, const std::string& name);
    LightFreighter(int id, const std::string& name, int maxCapacity);

    double  calculateFuel(int distance)         const override;
    Vessel* clone()                             const override;
    void    display()                           const override;
    void    writeReport(std::ofstream& out)     const override;
};

#endif // LIGHTFREIGHTER_H
