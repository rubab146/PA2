#include "../include/StealthRunner.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

StealthRunner::StealthRunner(int id, const std::string& name, double cloakRating)
    : Vessel(id, name) {
    // TODO
    if (cloakRating<0.0)
    {
        cloakRating=0.0;
    }
    if (cloakRating>1.0)
    {
        cloakRating=1.0;
    }
    this->cloakRating=cloakRating;
}

StealthRunner::StealthRunner(int id, const std::string& name,
                             int maxCapacity, double cloakRating)
    : Vessel(id, name, maxCapacity) {
    // TODO
        if (cloakRating<0.0)
    {
        cloakRating=0.0;
    }
    if (cloakRating>1.0)
    {
        cloakRating=1.0;
    }
    this->cloakRating=cloakRating;
}

double StealthRunner::getCloakRating() const {
    // TODO
    return cloakRating; // placeholder
}

double StealthRunner::calculateFuel(int distance) const {
    // TODO
    return distance * getTotalWeight() * cloakRating; // placeholder
}

Vessel* StealthRunner::clone() const {
    // TODO
    return new StealthRunner(*this); // placeholder
}

void StealthRunner::display() const {
    // TODO
    cout<<std::fixed<<std::setprecision(2)<<"Vessel: "<<getName()<<" [Type: StealthRunner | CloakRating: "<<getCloakRating()<< "]"<< " Cargo Items: "<< getCurrentLoad()<<" / "<< getMaxCapacity()<<endl;
    cout<<"Total Effective Weight: " << getTotalWeight() <<" kg"<<endl;
    cout <<"Fuel Required (100 ly): " << calculateFuel(100) <<" units"<<endl;
    cout << setfill('-')<<setw(42)<<""<<endl;
}

void StealthRunner::writeReport(std::ofstream& out) const {
    // TODO
    out<<std::fixed<<std::setprecision(2)<<"Vessel: "<<getName()<<" [Type: StealthRunner | CloakRating: "<<getCloakRating()<< "]"<< " Cargo Items: "<< getCurrentLoad()<<" / "<< getMaxCapacity()<<endl;
    out<<"Total Effective Weight: " << getTotalWeight() <<" kg"<<endl;
    out <<"Fuel Required (100 ly): " << calculateFuel(100) <<" units"<<endl;
    out << setfill('-')<<setw(42)<<""<<endl;
}

