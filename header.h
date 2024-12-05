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

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};
struct Tree {
    TreeNode* root;
    Tree() : root(nullptr) {};

    ~Tree();
    void Destroy(TreeNode* node);
    TreeNode* DeleteNode(TreeNode* root, int key);
    TreeNode* InsertRecursive(TreeNode* node, int value);
    int Height(TreeNode* node);
    int TreeHeight();
    void Insert(int value);
    void Print(const string& prefix, TreeNode* node, bool isLeft);
};

struct NodeHash {
    string key;
    string value;
    NodeHash* next;

    NodeHash(string& k, string& v) : key(k), value(v), next(nullptr) {}
};
struct HashTable {
    NodeHash** table; // массив указателей на узлы хеш-таблицы
    int size;
    int count;

    HashTable(int initialSize = 100);
    int HashFunc(string& str);
    void HPUSH(string& key, string& value);
    string HGET(string& key);
    void HDEL(string& key);
    void HREAD();

    void HDestroyTable(NodeHash* node);
    ~HashTable();
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

bool MatchPattern(Array& strArray, Array& patternArray, int sIndex, int pIndex);
void TestPatternMatch(Array& strArray, Array& patternArray);
SetNode* SetUnion(const SetNode& set1, const SetNode& set2);
SetNode* SetIntersection(const SetNode& set1, const SetNode& set2);
SetNode* SetDifference(const SetNode& set1, const SetNode& set2);
void ProcessingExpression(const string& oper, Stack& stackOper, Stack& stackNumb, string current, bool parameter);
bool isIsomorphic(string& A,string& B);