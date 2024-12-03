#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct SingleNode {
    string cell;
    SingleNode* next;
};

struct Set {
    string value;
};
struct SetNode {
    int size;
    Set** plenty;

    SetNode(int cap);
    ~SetNode();
    int HashSet(string itemKey) const;
    bool isFull();
    bool FindValue(string value, int& znach) const;
    void SETADD(string value);
    void SETDEL(string value);
    void SET_AT(string value);
};

struct Stack {
    int size;
    string cell;
    ~Stack();
    SingleNode* head;
    SingleNode* tail;
    void SPUSH(string& cell);
    void SPOP();
    void SREAD();
    void Clear();
    void DeleteTail();
    void DelElementValue(SingleNode* target);
    void AddTail(string& cell);

    Stack() : size(0), head(nullptr), tail(nullptr) {
    }
};

struct Array {
    string* data;
    int size;
    int maxSize;

    Array();
    ~Array();
    void MPUSHend(string& value);
    void MPUSHindex(const int& index, string& value);
    void MPUSHfromString(const string& value);
    string MGETL(const int& index);
    void MDEL(const int& index);
    void MREPL(const int& index, string& value);
    int MSIZE();
    void MREAD();
};

void ProcessingExpression(const string& oper, Stack& stackOper, Stack& stackNumb, string current, bool parameter);