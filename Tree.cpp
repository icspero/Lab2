#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#include "header.h"

Tree::~Tree() {
    Destroy(root);
}

void Tree::Destroy(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    Destroy(node->left);
    Destroy(node->right);
    delete node;
}

void Tree::Insert(int value) {
    root = InsertRecursive(root, value);
}

TreeNode* Tree::InsertRecursive(TreeNode* node, int value) {
    if (node == nullptr) {
        return new TreeNode(value);
    }

    if (value < node->value) {
        node->left = InsertRecursive(node->left, value);
    }
    else if (value > node->value) {
        node->right = InsertRecursive(node->right, value);
    }
    return node;
}

int Tree::Height(TreeNode* node) {
    if (node == nullptr) {
        return -1; // Пустое дерево имеет высоту -1, чтобы первый уровень был нулевым
    }
    int leftHeight = Height(node->left);
    int rightHeight = Height(node->right);
    return 1 + max(leftHeight, rightHeight); // Текущий уровень + максимальная глубина поддеревьев
}

int Tree::TreeHeight() {
    return Height(root);
}

void Tree::Print(const string& prefix,TreeNode* node, bool isLeft) {
    if (node != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "L--");

        cout << node->value << endl;

        Print(prefix + (isLeft ? "|   " : "    "), node->right, true);
        Print(prefix + (isLeft ? "|   " : "    "), node->left, false);
    }
}