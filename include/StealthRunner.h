#ifndef STEALTHRUNNER_H
#define STEALTHRUNNER_H

#include "Vessel.h"
#include <fstream>
#include <string>

class StealthRunner : public Vessel {
private:
    double cloakRating;

public:
    StealthRunner(int id, const std::string& name, double cloakRating);

    StealthRunner(int id, const std::string& name,
                  int maxCapacity, double cloakRating);

    double  getCloakRating()                    const;
    double  calculateFuel(int distance)         const override;
    Vessel* clone()                             const override;
    void    display()                           const override;
    void    writeReport(std::ofstream& out)     const override;
};

#endif // STEALTHRUNNER_H
