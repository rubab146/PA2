#ifndef CARGO_H
#define CARGO_H

#include "Entity.h"
#include <string>

class Cargo : public Entity {
private:
    static int  totalCargoCreated;
    std::string description;
    double      weight;

public:
    Cargo(int id, const std::string& description, double weight);
    virtual ~Cargo();

    std::string getDescription() const;
    double      getWeight()      const;
    static int  getTotalCargoCreated();
    void setTotalCargoCreated(int newTotalCargoCreated);

    virtual double  getEffectiveWeight() const = 0;
    virtual Cargo*  clone()                    = 0;
    virtual void    display()            const override;
};

#endif // CARGO_H
