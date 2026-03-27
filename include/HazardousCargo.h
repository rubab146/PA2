#ifndef HAZARDOUSCARGO_H
#define HAZARDOUSCARGO_H

#include "Cargo.h"
#include <string>

class HazardousCargo : public Cargo {
private:
    int hazardLevel;

public:
    HazardousCargo(int id, const std::string& description, double weight);

    HazardousCargo(int id, const std::string& description,
                   double weight, int hazardLevel);

    int     getHazardLevel()         const;
    double  getEffectiveWeight()     const override;
    Cargo*  clone()                  override;
    void    display()                const override;
};

#endif // HAZARDOUSCARGO_H
