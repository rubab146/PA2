#include "Cargo.h"
#include <iostream>
#include <iomanip>
using namespace std;

// static member definition
int Cargo::totalCargoCreated = 0;

Cargo::Cargo(int id, const std::string& description, double weight)
    : Entity(id, description),description(description),weight(weight)
    {
        totalCargoCreated++;
    }
Cargo::~Cargo() {
    // TODO
    totalCargoCreated--;
}

std::string Cargo::getDescription() const {
    // TODO
    return description; // placeholder
}

double Cargo::getWeight() const {
    // TODO
    return weight ; // placeholder
}

int Cargo::getTotalCargoCreated() {
    // TODO
    return totalCargoCreated; // placeholder
}

void Cargo::setTotalCargoCreated(int newTotalCargoCreated) {
    // TODO
    totalCargoCreated=newTotalCargoCreated;
}

void Cargo::display() const {
    // TODO
    cout<<"  [ Cargo ]"<<getDescription()<<" Raw : "<<std::fixed<<std::setprecision(2)<<getWeight()<<" kg" <<" Effective : " <<getEffectiveWeight()<<" kg";
}