#include "../include/PerishableCargo.h"
#include <iostream>
using namespace std;

PerishableCargo::PerishableCargo(int id, const std::string& description,
                                 double weight, int expiryDays)
    : Cargo(id, description, weight) {
    // TODO
    if (expiryDays<=0)
    {
        /* code */
        std::cerr << "Invalid expiryDays. Defaulting to 1.\n";
        expiryDays=1;
    }
        this->expiryDays=expiryDays;
}

int PerishableCargo::getExpiryDays() const {
    // TODO
    return expiryDays; // placeholder
}

double PerishableCargo::getEffectiveWeight() const {
    // TODO
    return getWeight()+5.00; // placeholder
}

Cargo* PerishableCargo::clone() {
    // TODO
    setTotalCargoCreated(getTotalCargoCreated() + 1);
    return new PerishableCargo(*this); // placeholder
}

void PerishableCargo::display() const {
    // TODO
    Cargo::display();
    cout <<" [Type: Perishable | Expires in: " <<getExpiryDays()<<" days]"<<endl;
}
