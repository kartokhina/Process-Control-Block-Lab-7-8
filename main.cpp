
#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include "processlist.h"


using namespace std;

int main() {
    //кодировки для Windows
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    ProcessList processes;


    PCB proc1, proc2, proc3, proc4;

    proc1.processID = 101;
    proc1.processName = "Process1";
    proc1.processStatus = "Running";
    proc1.commandCounter = 500;
    proc1.cpuRegisters[0] = 10; proc1.cpuRegisters[1] = 20;
    proc1.cpuRegisters[2] = 30; proc1.cpuRegisters[3] = 40;

    proc2.processID = 102;
    proc2.processName = "Process2";
    proc2.processStatus = "Waiting";
    proc2.commandCounter = 300;
    proc2.cpuRegisters[0] = 50; proc2.cpuRegisters[1] = 60;
    proc2.cpuRegisters[2] = 70; proc2.cpuRegisters[3] = 80;

    proc3.processID = 102;
    proc3.processName = "Process3";
    proc3.processStatus = "Stopped";
    proc3.commandCounter = 150;
    proc3.cpuRegisters[0] = 90; proc3.cpuRegisters[1] = 100;
    proc3.cpuRegisters[2] = 110; proc3.cpuRegisters[3] = 120;

  
    processes.insert(proc1);
    processes.insert(proc2);
    processes.insert(proc3);

    cout << "Список процессов после добавления:" << endl;
    processes.printList();

  
    processes.remove(102);

    cout << "\nУдалили процесс 102:" << endl;
    processes.printList();


    proc4.processID = 101;  
    proc4.processName = "Duplicate";
    proc4.processStatus = "Running";
    proc4.commandCounter = 400;
    
    if (!processes.insert(proc4)) {
        cout << "\nНе удалось добавить процесс 101 (дубликат)" << endl;
    }


    if (!processes.remove(999)) {
        cout << "Не удалось удалить процесс 999 (не существует)" << endl;
    }

    cout << "\nИтоговый список:" << endl;
    processes.printList();

    return 0;
}