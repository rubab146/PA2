#include "../include/HazardousCargo.h"
#include <iostream>
using namespace std;

HazardousCargo::HazardousCargo(int id, const std::string& description, double weight)
    : Cargo(id, description, weight) {
    // TODO
        hazardLevel=1;

}

HazardousCargo::HazardousCargo(int id, const std::string& description,
                               double weight, int hazardLevel)
    : Cargo(id, description, weight) {
    // TODO
        if(hazardLevel<1){
            hazardLevel=1;
        }
        if(hazardLevel>5){
            hazardLevel=5;
        }
        this->hazardLevel=hazardLevel;
    
}

int HazardousCargo::getHazardLevel() const {
    // TODO
    return hazardLevel; // placeholder
}

double HazardousCargo::getEffectiveWeight() const {
    // TODO
    return getWeight()*1.2; // placeholder
}

Cargo* HazardousCargo::clone() {
    // TODO
    totalCargoCreated++;
    return new HazardousCargo(*this);}

void HazardousCargo::display() const {
    // TODO 
       Cargo::display();
       cout <<" [Type: Hazardous | Level:" <<getHazardLevel()<<" ]";

}