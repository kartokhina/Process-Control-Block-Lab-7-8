 
 #include "processlist.h"
 #include <iostream>
 using namespace std;

ProcessList::ProcessList() : head(nullptr) {}

ProcessList::~ProcessList() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->getNext();
        delete current;
        current = nextNode;
    }
}

bool ProcessList::findPID(int pid){
    //есть ли процесс с таким номером
    ListNode* current = head;
    while (current != nullptr){
        if (current->getData().processID == pid){
            return true;
        }
        current = current->getNext();
    }
    return false;
}

bool ProcessList::insert(const PCB& newPCB){
//Вставляет новый PCB в список, упорядоченно по 
//идентификатору процесса. Возвращает true, если вставка успешна, и false в случае 
//дублирования идентификатора.
    if (findPID(newPCB.processID)){
        return false;
    }

    ListNode* newNode = new ListNode(newPCB);

    if (head == nullptr || head->getData().processID > newPCB.processID) {
        newNode->setNext(head);
        head = newNode;
        return true;
    }


    // Куда вставить
    ListNode* current = head;
    //"ПОКА (следующая нода существует) И (номер следующей ноды < номер новой)"
    while (current->getNext() != nullptr && current->getNext()->getData().processID < newPCB.processID) {
        current = current->getNext();
    }

    newNode->setNext(current->getNext());
    current->setNext(newNode);
    
    return true;

}

bool ProcessList::remove(int pid){
    if(head == nullptr){
        return false;
    }
    //если элемент первый
    if (head->getData().processID == pid){
      ListNode* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    ListNode* current = head;
    while (current->getNext() != nullptr && 
           current->getNext()->getData().processID != pid) {
        current = current->getNext();
    }
    
    //элемент не найден
    if (current->getNext() == nullptr) {
        return false;
    }

    //удаление
    ListNode* temp = current->getNext();
    current->setNext(temp->getNext());
    delete temp;
    
    return true;
}

void ProcessList::printList(){
    ListNode* current = head;

    if (current == nullptr) {
        cout << "The list is empty." << endl;
        return;
    }
    
    while (current != nullptr){
        PCB pcb = current->getData();
        
        cout << "Process ID: " << pcb.processID << endl;
        cout << "Name: " << pcb.processName << endl;
        cout << "Status: " << pcb.processStatus << endl;
        cout << "Command Counter: " << pcb.commandCounter << endl;
        cout << "CPU Registers: ";
        for (int i = 0; i < 4; i++) {
            cout << pcb.cpuRegisters[i] << " ";
        }
        cout << "\n\n";

        current = current->getNext();

    }
}
