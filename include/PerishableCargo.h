#ifndef PERISHABLECARGO_H
#define PERISHABLECARGO_H

#include "Cargo.h"
#include <string>

class PerishableCargo : public Cargo {
private:
    int expiryDays;

public:
    PerishableCargo(int id, const std::string& description,
                    double weight, int expiryDays);

    int     getExpiryDays()          const;
    double  getEffectiveWeight()     const override;
    Cargo*  clone()                  override;
    void    display()                const override;
};

#endif // PERISHABLECARGO_H
