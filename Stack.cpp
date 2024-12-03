#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "header.h"

using namespace std;

Stack::~Stack() {
    while (head != nullptr) {
        SingleNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

void Stack::SPUSH(string& cell) {
    
    SingleNode* node = new SingleNode;
    node->cell = cell;
    node->next = nullptr;

    if (head == nullptr) {
        head = tail = node;
    }
    else {
        node->next = head;
        head = node;
    }
}

void Stack::SPOP() {
    if (head == tail) {  
        delete head;      
        head = tail = nullptr; 
        return;
    }
    SingleNode* current = head;
    head = head->next;
    delete current;
}
void Stack::SREAD() {
    SingleNode* current = head;
    cout << endl;
    while (current != nullptr) {
        cout << current->cell << " ";
        current = current->next;
    }
    cout << endl;
}

void Stack::DeleteTail() {
    if (head == nullptr) {
        cout << "\nThe list is empty!" << endl;
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        return;
    }

    SingleNode* current = head;
    while (current->next != tail) { 
        current = current->next;
    }

    delete tail;
    tail = current;
    tail->next = nullptr; 
}

void Stack::AddTail(string&cell) {

   SingleNode* node = new SingleNode;
    node->cell = cell;
    node->next = nullptr;
    if (tail == nullptr) {
        head = tail = node;
        tail->next = nullptr;
    }
    else {
        tail->next = node;
        tail = node;
        tail->next = nullptr;
        
    }
}

void Stack::DelElementValue(SingleNode* target) {
    if (head == nullptr) {
        return;
    }
    if (head == target) {
        size--;
        SPOP();
        return;
    }

    SingleNode* current = head;
    while (current != nullptr && current->next != target) {
        current = current->next;
    }
    if (current != nullptr && current->next == target) {
        SingleNode* temp = current->next;
        if (current->next != nullptr) {
            current->next = current->next->next;
        }
        else {
            current->next = nullptr;
        }

        delete temp;
    }
    size--;
}

void ProcessingExpression(const string& oper, Stack& stackOper, Stack& stackNumb, string current, bool parameter) {

    stackOper.DeleteTail();
    int A = 0;
    int B = stoi(stackNumb.tail->cell);
    stackNumb.DeleteTail();
    if (parameter == 1) {
        A = stoi(stackNumb.tail->cell);
        A = A * (-1);
    }
    else {
        A = stoi(stackNumb.tail->cell);
    }

    stackNumb.DeleteTail();

    int result;
    if (oper == "*") result = A * B;
    if (oper == "+") result = A + B;
    if (oper == "-") result = A - B;
    if (result < 0 && parameter == 1) {
        result = result * (-1);
    }
    string temp = to_string(result);
    stackNumb.AddTail(temp);
    stackOper.AddTail(current);

}