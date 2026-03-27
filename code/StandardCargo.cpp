#include "../include/StandardCargo.h"
#include <iostream>
using namespace std;
StandardCargo::StandardCargo(int id, const std::string& description, double weight)
    : Cargo(id, description, weight) {
    // TODO
}

double StandardCargo::getEffectiveWeight() const {
    // TODO
    return getWeight(); // placeholder
}

Cargo* StandardCargo::clone() {
    // TODO
    return new StandardCargo(*this); // placeholder
}

void StandardCargo::display() const {
    // TODO
   Cargo::display();
   cout<<" [Type: Standard]"<<endl;
}
