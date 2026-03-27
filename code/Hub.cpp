#include "../include/Hub.h"
#include "../include/LightFreighter.h"
#include "../include/HeavyLifter.h"
#include "../include/StealthRunner.h"
#include "../include/StandardCargo.h"
#include "../include/HazardousCargo.h"
#include "../include/PerishableCargo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// -------- private helper functions --------
void Hub::appendLog(const std::string &desc, const std::string &vessel)
{
    // TODO
    CargoLog *newNode = new CargoLog(desc,vessel);
    if (logHead == nullptr)
    {
        logHead = newNode;
    }
    else
    {
        CargoLog *temp = logHead;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void Hub::clearLog()
{
    // TODO
    CargoLog *current = logHead;
    while (current != nullptr)
    {
        CargoLog *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    logHead = nullptr;
}

// ------------------------------------------

Hub::Hub()
{
    // TODO
    dockCapacity = 20;
    dock = new Vessel *[20];
    for (int i = 0; i < dockCapacity; i++)
    {
        dock[i] = nullptr;
    }
    numVessels = 0;
    logHead = nullptr;
}

Hub::Hub(const Hub &other)
{
    // TODO
    this->numVessels = other.numVessels;
    this->dockCapacity = other.dockCapacity;
    dock = new Vessel *[dockCapacity];
    for (int i = 0; i < dockCapacity; i++)
    {
        if (other.dock[i] != nullptr)
        {
            dock[i] = other.dock[i]->clone();
        }
        else
        {
            dock[i] = nullptr;
        }
    }
    CargoLog *current = other.logHead;
    while (current)
    {
        appendLog(current->cargoDescription, current->vesselName);
        current = current->next;
    }
}

Hub &Hub::operator=(const Hub &other)
{
    // TODO
    if (this == &other)
    {
        return *this;
    }
    for (int i = 0; i < dockCapacity; i++)
    {
        if (dock[i] != nullptr)
        {
            delete dock[i];
        }
    }
    delete[] dock;
    clearLog();

    this->numVessels = other.numVessels;
    this->dockCapacity = other.dockCapacity;
    this->dock = new Vessel *[dockCapacity];

    for (int i = 0; i < dockCapacity; i++)
    {
        if (other.dock[i] != nullptr)
        {
            this->dock[i] = other.dock[i]->clone();
        }
        else
        {
            this->dock[i] = nullptr;
        }
    }
    CargoLog *current = other.logHead;
    while (current != nullptr)
    {
        appendLog(current->cargoDescription, current->vesselName);
        current = current->next;
    }

    return *this;
}

Hub::~Hub()
{
    // TODO
    for (int i = 0; i < dockCapacity; i++)
    {
        if (dock[i] != nullptr)
        {
            delete dock[i];
            dock[i] = nullptr;
        }
    }
    delete[] dock;
    dock = nullptr;
    clearLog();
}

void Hub::addVessel(Vessel *v)
{
    // TODO
    if (numVessels == dockCapacity)
    {
        cout << "Dock is full. Cannot add more vessels." << endl;
        delete v;
        return;
    }
    else
    {
        dock[numVessels] = v;
        numVessels++;
    }
}

Vessel *Hub::findVessel(const std::string &name) const
{
    // TODO
    for (int i = 0; i < dockCapacity; i++)
    {
        if (dock[i] != nullptr)
        {
            if (dock[i]->getName() == name)
            {
                return dock[i];
            }
        }
    }

    return nullptr; // placeholder
}

Vessel *Hub::findVessel(int index) const
{
    // TODO
    if (index >= 0 && index < numVessels)
    {
        return dock[index];
    }

    return nullptr; // placeholder
}
void Hub::Addtoship(stringstream &data, Vessel *ship)
{
    string type, desc;
    double weight;
    int id;
    data >> type;
    data >> id;
    data >> desc;
    data >> weight;

    if (weight < 0)
    {
        return;
    }
    Cargo *item = nullptr;
    if (type == "Standard")
    {
        item = new StandardCargo(id, desc, weight);
    }
    else if (type == "Hazardous")
    {
        int hazardlevel;
        data >> hazardlevel;
        item = new HazardousCargo(id, desc, weight, hazardlevel);
    }
    else if (type == "Perishable")
    {
        int expirydays;
        data >> expirydays;
        item = new PerishableCargo(id, desc, weight, expirydays);
    }
    else
    {
        cout << "Unknown cargo type" << endl;
        return;
    }
    if (ship->getCurrentLoad() == ship->getMaxCapacity())
    { 
        ship->addCargo(item);
        delete item;

    }
    else
    {  
        ship->addCargo(item);
        appendLog(desc, ship->getName());
    }
}

void Hub::loadFleet(const char *filename)
{
    // TODO
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    Vessel *current = nullptr;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        stringstream data(line);
        string firstword;
        data >> firstword;
        if (firstword == "VESSEL")
        {
            string model;
            string name;
            int id;
            data >> model >> id >> name;
            if (model == "LightFreighter")
            {
                current = new LightFreighter(id, name);
            }
            else if (model == "HeavyLifter")
            {
                current = new HeavyLifter(id, name);
            }
            else if (model == "StealthRunner")
            {
                double cloakrating;
                data >> cloakrating;
                current = new StealthRunner(id, name, cloakrating);
            }
            else
            {
                cout << "Unknown vessel type" << endl;
                while (getline(file, line) && line != "END")
                {
                    current = nullptr;
                }
            }
        }
        else if (firstword == "CARGO")
        {
            if (current != nullptr)
            {
                Addtoship(data, current);
            }
        }
        else if (firstword == "END")
        {
            if (current != nullptr)
            {
                addVessel(current);
                current = nullptr;
            }
        }
    }
    if (current != nullptr)
    {
        addVessel(current);
    }

    file.close();
}

void Hub::processLogistics() const
{
    // TODO
    for (int i = 0; i < numVessels; i++)
    {
        if (dock[i] != nullptr)
        {
            dock[i]->display();
        }
    }
}

void Hub::printLog() const
{
    // TODO
    if (logHead == nullptr)
    {
        cout << "No cargo log entries." << endl;
        return;
    }

    CargoLog *current = logHead;
    while (current != nullptr)
    {
        cout << "[LOG] " << current->cargoDescription << " loaded onto " << current->vesselName << endl;
        current = current->next;
    }
}

void Hub::saveReport(const char *filename) const
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cerr << "Error writing report." << endl;
        return;
    }

    out << "===== Galactic Logistics Hub Report =====" << endl;

    for (int i = 0; i < numVessels; i++)
    {
        if (dock[i] != nullptr)
        {
            dock[i]->writeReport(out);
        }
    }

    out << "===== Cargo Load Log =====" << endl;
    CargoLog *current = logHead;
    while (current != nullptr)
    {
        out << "[LOG] " << current->cargoDescription << " loaded onto " << current->vesselName << endl;
        current = current->next;
    }

    out.close();
}
