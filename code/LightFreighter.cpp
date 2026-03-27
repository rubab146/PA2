#include "../include/LightFreighter.h"
#include <iostream>
#include <iomanip>
using namespace std;

LightFreighter::LightFreighter(int id, const std::string &name)
    : Vessel(id, name)
{
    // TODO
}

LightFreighter::LightFreighter(int id, const std::string &name, int maxCapacity)
    : Vessel(id, name, maxCapacity)
{
    // TODO
}

double LightFreighter::calculateFuel(int distance) const
{
    // TODO
    return distance * (getTotalWeight() * 0.5); // placeholder
}

Vessel *LightFreighter::clone() const
{
    // TODO
    return new LightFreighter(*this); // placeholder
}

void LightFreighter::display() const
{
    // TODO
    cout << std::fixed << std::setprecision(2) << "Vessel: " << getName() << " [Type: LightFreighter] Cargo Items: " << getCurrentLoad() << "/" << getMaxCapacity() << endl;
    cout << "Total Effective Weight: " << getTotalWeight() << " kg" << endl;
    cout << "Fuel Required (100 ly): " << calculateFuel(100) << " units" << endl;
    cout << "------------------------------------------" << endl;
}

void LightFreighter::writeReport(std::ofstream &out) const
{
    // TODO
    out << std::fixed << std::setprecision(2) << "Vessel: " << getName() << " [Type: LightFreighter] Cargo Items: " << getCurrentLoad() << "/" << getMaxCapacity() << endl;
    out << "Total Effective Weight: " << getTotalWeight() << " kg" << endl;
    out << "Fuel Required (100 ly): " << calculateFuel(100) << " units" << endl;
    out << "------------------------------------------" << endl;
}
