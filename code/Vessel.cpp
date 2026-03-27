#include "../include/Vessel.h"
#include <iostream>
using namespace std;
// static member definition
int Vessel::totalVesselsCreated = 0;

Vessel::Vessel(int id, const std::string &name)
    : Entity(id, name)
{
    // TODO
    maxCapacity = 10;
    currentLoad = 0;
    manifest = new Cargo *[10];
    for (int i = 0; i < 10; i++)
    {
        manifest[i] = nullptr;
    }
    totalVesselsCreated++;
}

Vessel::Vessel(int id, const std::string &name, int maxCapacity)
    : Entity(id, name)
{
    // TODO
    if (maxCapacity > 0)
    {
        currentLoad = 0;
        this->maxCapacity = maxCapacity;

        manifest = new Cargo *[maxCapacity];
        for (int i = 0; i < maxCapacity; i++)
        {
            manifest[i] = nullptr;
        }
        totalVesselsCreated++;
    }
}
Vessel::Vessel(const Vessel &other)
    : Entity(other)
{
    // TODO
    this->currentLoad = other.currentLoad;
    this->maxCapacity = other.maxCapacity;
    manifest = new Cargo *[maxCapacity];
    for (int i = 0; i < currentLoad; i++)
    {
        if (other.manifest[i] != nullptr)
        {
            manifest[i] = other.manifest[i]->clone();
        }
        else
        {
            manifest[i] = nullptr;
        }
    }
    for (int i = currentLoad; i < maxCapacity; i++)
    {
        manifest[i] = nullptr;
    }
    totalVesselsCreated++;
}
Vessel &Vessel::operator=(const Vessel &other)
{
    // TODO
    if (this == &other)
    {
        return *this;
    }
    for (int i = 0; i < currentLoad; i++)
    {
        if (manifest[i] != nullptr)
        {
            delete manifest[i];
            manifest[i] = nullptr;
        }
    }
    delete[] manifest;

    this->currentLoad = other.currentLoad;
    this->maxCapacity = other.maxCapacity;
    manifest = new Cargo *[maxCapacity];
    for (int i = 0; i < maxCapacity; i++)
    {
        manifest[i] = other.manifest[i]->clone();
    }
    return *this; // placeholder
}
Vessel::~Vessel()
{
    // TODO
    for (int i = 0; i < maxCapacity; i++)
    {
        if (manifest[i] != nullptr)
        {
            delete manifest[i];
            manifest[i] = nullptr;
        }
    }
    delete[] manifest;
    totalVesselsCreated--;
}
void Vessel::addCargo(Cargo *item)
{
    // TODO
    if (currentLoad == maxCapacity)
    {
        cout << "Cargo Capacity Reached!";
        return;
    }
    else
    {
        manifest[currentLoad] = item;
        currentLoad++;
    }
}
bool Vessel::addCargo(Cargo *item, int slot)
{
    // TODO
    if (slot >= 0 && slot < maxCapacity)
    {
        if (manifest[slot] == nullptr)
        {
            manifest[slot] = item;
            currentLoad++;
            return true;
        }
        else
        {
            cout << "Invalid slot or slot already occupied.";
        }
        return false; // placeholder
    }
    else
    {
        cout << "Invalid slot or slot already occupied."<<endl;
    }
    return false; // placeholder
}
double Vessel::getTotalWeight() const
{
    // TODO
    double totalweights = 0.0;
    for (int i = 0; i < currentLoad; i++)
    {
        if (manifest[i] != nullptr)
        {
            totalweights += manifest[i]->getEffectiveWeight();
        }
    }
    return totalweights; // placeholder
}
int Vessel::getCurrentLoad() const
{
    // TODO
    return currentLoad; // placeholder
}
int Vessel::getMaxCapacity() const
{
    // TODO
    return maxCapacity; // placeholder
}
int Vessel::getTotalVesselsCreated()
{
    // TODO
    return totalVesselsCreated; // placeholder
}
