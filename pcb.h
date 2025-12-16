
#ifndef PCB_H
#define PCB_H

#include <string>


struct PCB
{
    int processID;
    std::string processName;
    std::string processStatus;
    int cpuRegisters[4];
    int commandCounter;
};
#endif