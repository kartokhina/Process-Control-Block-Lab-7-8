


#include "listnode.h"

ListNode::ListNode(const PCB& pcb): data(pcb),  next(nullptr){}

ListNode::~ListNode(){
    //Нет динамическоц памяти, поэтому деструктор пустой
}

PCB ListNode::getData(){
    return data;
}
ListNode*  ListNode::getNext(){
    return next;
}
void ListNode::setNext(ListNode* node){
    next = node;
}