#ifndef STANDARDCARGO_H
#define STANDARDCARGO_H

#include "Cargo.h"
#include <string>

class StandardCargo : public Cargo {
public:
    StandardCargo(int id, const std::string& description, double weight);

    double  getEffectiveWeight() const override;
    Cargo*  clone()              override;
    void    display()            const override;
};

#endif // STANDARDCARGO_H
