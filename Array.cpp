#include "header.h"
#include <iostream>
#include <fstream>

using namespace std;

Array::Array() : size(0), maxSize(100) {
    data = new string[maxSize];
}

Array::~Array() {
    delete[] data;
}

void Array::MPUSHend(string& value) {
    data[size++] = value;
}

void Array::MPUSHindex(const int& index, string& value) {
    if (index < 0 || index >= size ) {
        cout << endl << "Incorrect input!" << endl;
        return;
    }
    for (int i = size; i > index; i--) { 
        data[i] = data[i - 1];
    }
    data[index] = value + " ";
    size++; 
}

string Array::MGETL(const int& index) {
    if (index < 0 || index >= size ) {
        cout << endl << "Incorrect input!" << endl;
        return "error";
    }
    return data[index]; 
}

void Array::MDEL(const int& index) {
    if (index < 0 || index >= size ) {
        cout << endl << "Incorrect input!" << endl;
        return;
    }
    for (int i = index; i < size - 1; i++) { 
        data[i] = data[i + 1];
    }
    size--; 
}

void Array::MREPL(const int& index, string& value) {
    if (index < 0 || index >= size ) {
        cout << endl << "Incorrect input!" << endl;
        return;
    }
    data[index] = " " + value + " "; 
}

int Array::MSIZE() {
    return size;  
}

void Array::MREAD() {
    cout << endl;
    for (int i = 0; i < size; i++) {  
        cout << "[ " << data[i] << " ]" << endl;
    }
    cout << endl;
}

void Array::MPUSHfromString(const string& value) {
    for (char ch : value) {
        string s(1, ch); // Преобразуем символ в строку
        MPUSHend(s); // Добавляем символ как строку
    }
}

bool MatchPattern(Array& strArray, Array& patternArray, int sIndex = 0, int pIndex = 0) {
    // Если оба индекса дошли до конца, совпадение
    if (sIndex == strArray.MSIZE() && pIndex == patternArray.MSIZE()) {
        return true;
    }

    // Если шаблон исчерпан, но строка еще есть, нет совпадения
    if (pIndex == patternArray.MSIZE()) {
        return false;
    }

    // Если текущий символ шаблона '*'
    if (patternArray.MGETL(pIndex) == "*") {
        // Проверяем две возможности:
        // 1. '*' соответствует пустой последовательности
        // 2. '*' соответствует одному или более символам строки
        return MatchPattern(strArray, patternArray, sIndex, pIndex + 1) || 
               (sIndex < strArray.MSIZE() && MatchPattern(strArray, patternArray, sIndex + 1, pIndex));
    }

    // Если текущий символ шаблона '?' или совпадает с символом строки
    if (sIndex < strArray.MSIZE() && 
        (patternArray.MGETL(pIndex) == "?" || patternArray.MGETL(pIndex) == strArray.MGETL(sIndex))) {
        return MatchPattern(strArray, patternArray, sIndex + 1, pIndex + 1);
    }

    // В остальных случаях совпадения нет
    return false;
}

void TestPatternMatch(Array& strArray, Array& patternArray) {
    if (MatchPattern(strArray, patternArray)) {
        cout << "The string matches the pattern!" << endl;
    } else {
        cout << "The string does not match the pattern!" << endl;
    }
}