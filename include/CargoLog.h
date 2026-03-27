#ifndef CARGOLOG_H
#define CARGOLOG_H

#include <string>

struct CargoLog {
    std::string cargoDescription;
    std::string vesselName;
    CargoLog*   next;

    CargoLog(const std::string& desc, const std::string& vessel);
};

#endif // CARGOLOG_H
