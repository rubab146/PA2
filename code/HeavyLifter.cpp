#include "../include/HeavyLifter.h"
#include <iostream>
#include <iomanip>
using namespace std;
HeavyLifter::HeavyLifter(int id, const std::string& name)
    : Vessel(id, name) {
    // TODO
}

HeavyLifter::HeavyLifter(int id, const std::string& name, int maxCapacity)
    : Vessel(id, name, maxCapacity) {
    // TODO
}

double HeavyLifter::calculateFuel(int distance) const {
    // TODO
    return (distance * getTotalWeight() * 1.5) + 500; // placeholder
}

Vessel* HeavyLifter::clone() const {
    // TODO
    return new HeavyLifter(*this) ; 
}

void HeavyLifter::display() const {
    // TODO
    cout<<std::fixed<<std::setprecision(2)<<"Vessel: "<<getName()<<" [Type: HeavyLifter] Cargo Items :"<< getCurrentLoad()<<"/"<< getMaxCapacity()<<endl;
    cout<<"Total Effective Weight: " <<fixed<<setprecision(2)<< getTotalWeight() <<" Kg"<<endl;
    cout <<"Fuel Required (100 ly ):" << calculateFuel(100) <<" units"<<endl;
    cout << "------------------------------------------\n";
}

void HeavyLifter::writeReport(std::ofstream& out) const {
    // TODO
    out<<std::fixed<<std::setprecision(2)<<"Vessel: "<<getName()<<" [Type: HeavyLifter] Cargo Items :"<< getCurrentLoad()<<"/"<< getMaxCapacity()<<endl;
    out<<"Total Effective Weight: " <<fixed<<setprecision(2)<< getTotalWeight() <<" Kg"<<endl;
    out <<"Fuel Required (100 ly ):" << calculateFuel(100) <<" units"<<endl;
    out << "------------------------------------------\n";
}
}
