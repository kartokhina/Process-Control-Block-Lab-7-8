#ifndef LISTNODE_H
#define LISTNODE_H


#include "pcb.h"

class ListNode{
    private:
        PCB data;
        ListNode* next;

    public:
        ListNode(const PCB& pcb);

        ~ListNode();

        PCB getData();
        ListNode* getNext();

        void setNext(ListNode* node);
};


#endif   