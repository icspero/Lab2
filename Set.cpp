#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "header.h"

using namespace std;

SetNode::SetNode(int cap) : size(cap) {
    plenty = new Set * [size];
    for (int i = 0; i < size; i++) {
        plenty[i] = nullptr;
    }
}

SetNode::~SetNode(){
    for (int i = 0; i < size; ++i) {
        delete plenty[i];
    }
    delete[] plenty;
}

int SetNode::HashSet(string itemKey) const {
    int result = 0;
    for (char i : itemKey) {
        result += static_cast<int>(i);
    }
    return abs(result) % size;
}

bool SetNode::isFull() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (plenty[i] != nullptr) {
            count++;
        }
    }
    return count >= size;
}
bool SetNode::FindValue(string value, int &result) const {
    int index = HashSet(value);  
    int newIndex = index; 

    for (int i = 0; i < size; i++) {
        if (plenty[index] == nullptr) {// элемент не найден
            result = -1;  
            return false;
        }
        if (plenty[index]->value == value) { //найден
            result = index;
            return true;
        }

        // если не найден, пробуем следующую ячейку с помощью второй хеш-функции
        index = (newIndex + i * HashSet(value)) % size;
    }

    result = -1;
    return false;
}

void SetNode::SETADD(string value) {
    int index = HashSet(value);
    // наличие уже такого же значения
    if (plenty[index] != nullptr && plenty[index]->value == value) {
        return;
    }
    // наличие уже такого ключа, если колизия его передвинула
    int result = 0;
    bool isExist = FindValue(value, result);
    if (isExist) {
        return;
    }
    if (isFull()) {
        cout << endl << "The set is crowded!" << endl;
        return;
    }
    //если есть место - используем
    if (plenty[index] == nullptr) {
        plenty[index] = new Set{value}; 
    }
    else { //иначе ищем другое свободное место
        for (int i = 1; i < size; i++) {
            // Используем метод пробирования с другой хеш-функцией или методом
            int newIndex = (index + i * HashSet(value)) % size;  // Пробирование с шагом через вторичную хеш-функцию
            
            if (plenty[newIndex] == nullptr) {
                plenty[newIndex] = new Set{value};  
                break; 
            }
        }
    }
}
void SetNode::SETDEL(string value) {
    int index = HashSet(value);
    if (plenty[index] == nullptr) {
        cout << endl << "The element does not exist!" << endl;
        return;
    }
    if (plenty[index]->value == value) { //Если было без коллизий
        delete plenty[index];
        plenty[index] = nullptr;
        return;
    }

    bool isExist = FindValue(value, index);
    if (isExist) {
        delete plenty[index];
        plenty[index] = nullptr;
        return;
    }
}

void SetNode::SET_AT(string value) {

    int index = HashSet(value);
    if (plenty[index] == nullptr) {
        cout << endl << "The element was not found!" << endl;
        return;
    }
    if (plenty[index]->value == value) { //Если было без коллизий
        cout << endl << "The element was found!" << endl;
        return;
    }
    bool isExist = FindValue(value, index);
    if (isExist) {
        cout << endl << "The element was found!" << endl;
        return;
    }
    
}

SetNode* SetUnion(const SetNode& set1, const SetNode& set2) {
    SetNode* result = new SetNode(set1.size + set2.size); // Создаем множество с достаточным размером
    
    for (int i = 0; i < set1.size; i++) {
        if (set1.plenty[i] != nullptr) {
            result->SETADD(set1.plenty[i]->value);
        }
    }
    for (int i = 0; i < set2.size; i++) {
        if (set2.plenty[i] != nullptr) {
            result->SETADD(set2.plenty[i]->value);
        }
    }
    return result;
}

SetNode* SetIntersection(const SetNode& set1, const SetNode& set2) {
    SetNode* result = new SetNode(std::min(set1.size, set2.size)); // Максимально возможный размер пересечения
    
    for (int i = 0; i < set1.size; i++) {
        if (set1.plenty[i] != nullptr) {
            int dummy;
            if (set2.FindValue(set1.plenty[i]->value, dummy)) { // Если элемент есть в обоих множествах
                result->SETADD(set1.plenty[i]->value);
            }
        }
    }
    return result;
}

SetNode* SetDifference(const SetNode& set1, const SetNode& set2) {
    SetNode* result = new SetNode(set1.size); // Максимально возможный размер разности - размер первого множества
    
    for (int i = 0; i < set1.size; i++) {
        if (set1.plenty[i] != nullptr) {
            int dummy;
            if (!set2.FindValue(set1.plenty[i]->value, dummy)) { // Элемента нет во втором множестве
                result->SETADD(set1.plenty[i]->value);
            }
        }
    }
    return result;
}