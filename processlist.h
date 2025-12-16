#ifndef PROCESSLIST_H
#define PROCESSLIST_H


#include "listnode.h"

class ProcessList{
    private:
        ListNode* head;
        bool findPID(int pid);
    public:
        ProcessList();
        ~ProcessList();


        bool insert(const PCB& newPCB);
        bool remove(int pid);
        void printList();

};



#endif