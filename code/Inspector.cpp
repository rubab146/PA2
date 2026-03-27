#include "../include/Inspector.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Inspector::inspect(const Vessel& vessel) const {
    // TODO
    cout<< "=== Inspector Report: " <<vessel.getName()<< " ===" <<endl;
    cout<< "Capacity: "<<vessel.currentLoad<<" / "<<vessel.maxCapacity <<endl;
    cout<<"Manifest: "<<endl;

    for (int i = 0; i < vessel.maxCapacity; i++)
    {
        if (vessel.manifest[i]!=nullptr)
        {
           cout<< "[" << i << "] " << vessel.manifest[i]->getDescription()<<" | Effective: "<<fixed<<setprecision(2)<<vessel.manifest[i]->getEffectiveWeight() << " kg"<<endl;         
        }
        else{
            cout<<"[" << i << "] (empty)"<<endl; 
        }
    }
   cout << "================================="<<endl;
}

int Inspector::countNullSlots(const Vessel& vessel) const {
    // TODO
    int count=0;
    for (int i = 0; i < vessel.maxCapacity; i++)
    {
        if (vessel.manifest[i]==nullptr)
        {
            count++;
        }
        
    }
    return count;
}
