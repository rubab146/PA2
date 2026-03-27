#ifndef HUB_H
#define HUB_H

#include "Vessel.h"
#include "CargoLog.h"
#include <string>

class Hub {
private:
    Vessel**   dock;
    int        numVessels;
    int        dockCapacity;
    CargoLog*  logHead;

    void appendLog(const std::string& desc, const std::string& vessel);

    void clearLog();

public:
    Hub();
    Hub(const Hub& other);
    Hub& operator=(const Hub& other);
    ~Hub();

    void    addVessel(Vessel* v);

    Vessel* findVessel(const std::string& name) const;

    Vessel* findVessel(int index)               const;

    void loadFleet(const char* filename);
    void processLogistics()               const;
    void printLog()                       const;
    void saveReport(const char* filename) const;
};

#endif // HUB_H
