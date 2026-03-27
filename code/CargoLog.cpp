#include "../include/CargoLog.h"

CargoLog::CargoLog(const std::string& desc, const std::string& vessel) {
    // TODO
    cargoDescription=desc;
    vesselName=vessel;
    next=nullptr;
}
