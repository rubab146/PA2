#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "Vessel.h"

class Inspector {
public:
    void inspect(const Vessel& vessel) const;

    int  countNullSlots(const Vessel& vessel) const;
};

#endif // INSPECTOR_H
