# Process-Control-Block-Lab-7-8
# Лабораторная 7-8
ФИО: Картохина Виктория Алексеевна 

Группа: СКБ252


## Цель работы
Цель лабораторной работы — реализация класса на языке C++ для управления связанным 
списком блоков управления процессами (PCB). PCB (Process Control Block) — это структура данных, 
используемая операционной системой для хранения информации о состоянии процесса. Эта 
информация включает идентификатор процесса, его статус, счетчик команд, регистры CPU и 
другие данные, необходимые для управления выполнением процесса.


##  Описание алгоритма
Основные компоненты:
1. Структура PCB - содержит информацию о процессе

2. Класс ListNode - узел односвязного списка

3. Класс ProcessList - управление списком

Основные методы ProcessList:
1. insert() - вставляет новый PCB в упорядоченный список:

2. remove() - удаляет процесс по ID:

3. printList() - выводит информацию о всех процессах

4. findPID() - проверяет наличие процесса по ID


##  Код программы
# pcb.h
```cpp

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
```
# listnode.h
```cpp
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
```
# processlist.h
```cpp
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
```

#listnode.cpp
```cpp
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
```


# processlist.cpp
```cpp
 
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

```

# main.cpp (пример использования)
```cpp

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
```




##  Cсылка на репризиторий
Cсылка на репризиторий: https://github.com/kartokhina/Process-Control-Block-Lab-7-8

##  Вывод
В ходе выполнения лабораторной работы освоены принципы работы с динамическими структурами данных, корректное выделение и освобождение памяти, а также основные операции со списком: вставка с сохранением порядка, удаление, поиск и отображение элементов. 
