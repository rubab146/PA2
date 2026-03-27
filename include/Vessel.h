#ifndef VESSEL_H
#define VESSEL_H

#include "Entity.h"
#include "Cargo.h"
#include <fstream>
#include <string>

class Inspector; // forward declaration so we can declare it as a friend class

class Vessel : public Entity {
private:
    static int totalVesselsCreated;

    Cargo** manifest;
    int     currentLoad;
    int     maxCapacity;

    friend class Inspector;   // inspector may access private members directly

public:
    Vessel(int id, const std::string& name);

    Vessel(int id, const std::string& name, int maxCapacity);

    Vessel(const Vessel& other);
    Vessel& operator=(const Vessel& other);
    virtual ~Vessel();

    void addCargo(Cargo* item);

    bool addCargo(Cargo* item, int slot);

    double getTotalWeight()  const;
    int    getCurrentLoad()  const;
    int    getMaxCapacity()  const;
    static int getTotalVesselsCreated();

    virtual double  calculateFuel(int distance)          const = 0;
    virtual Vessel* clone()                              const = 0;
    virtual void    display()                            const override = 0;
    virtual void    writeReport(std::ofstream& out)      const = 0;
};

#endif // VESSEL_H
