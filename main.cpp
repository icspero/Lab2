#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "header.h"

using namespace std;

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

int main()
{  
    while (true) {

        cout << endl << "Select a task >>>> ";
        string numberTask;
        cin >> numberTask;

        if (numberTask == "exit") {
            break;
        } 
        else if (numberTask == "1") {
            Stack stackOper;
            Stack stackNumb;
            cout << endl << "Expression >>>> ";
            cin.ignore();
            string expression;

            getline(cin, expression);
            string expressionTemp = expression;
            stringstream ss(expression);
            string part;
            int countBrackets = 0;;
            int countOperators = 0;
            int countNumbers = 0;

            bool isWrong = false;
            string prev = "";
            while (getline(ss, part, ' ')) {
                if (part == "(") {
                    if (prev != "oper" && prev != "" && prev != "bracket") {
                        isWrong = true;
                        break;
                    }
                    prev = "bracket";
                    countBrackets++;

                }
                else if (part == ")") {
                    if (prev != "number" && prev != "bracket") {
                        isWrong = true;
                        break;
                    }
                    prev = "bracket";
                    countBrackets++;
                }
                else if (part == "+" || part == "-" || part == "*") {

                    if (prev != "number" && prev != "bracket") {
                        isWrong = true;
                        break;
                    }
                    prev = "oper";
                    countOperators++;

                }
                else if (isdigit(part.at(0)) || part.at(0) == '-') {
                    if (part.at(0) == '0') {
                        isWrong = true;
                        break;
                    }
                    int i = 1;
                    while (i != part.size()) {
                        if (isdigit(part.at(i)) == false) {
                            isWrong = true;
                            break;
                        }
                        i++;
                    }
                    if (prev != "oper" && prev != "bracket") {
                        if (prev != "") {
                            isWrong = true;
                            break;
                        }
                    }
                    prev = "number";
                    countNumbers++;
                }

                else {
                    isWrong = true;
                    break;
                }
            }
            if (isWrong) {
                cout << endl << "Incorrect input!" << endl;
                continue;
            }
            if (countBrackets % 2 != 0 || countNumbers - countOperators != 1) {
                cout << endl << "Incorrect input!" << endl;
                continue;
            }
            stringstream sss(expressionTemp);
            string current = "";

            while (getline(sss, current, ' ')) {
                if (current == "+" || current == "-" || current == "*") {
                    if (stackOper.tail == nullptr) {
                        stackOper.AddTail(current);
                        continue;
                    }
                    if (current == "+" || current == "-") {
                        if (stackOper.tail->cell == "*") {
                            ProcessingExpression("*", stackOper, stackNumb, current, 0);
                        }
                        else {
                            if (stackOper.tail->cell == "+" && current == "+") {
                                ProcessingExpression("+", stackOper, stackNumb, current, 0);
                            }
                            else {
                                stackOper.AddTail(current);
                                continue;
                            }
                        }
                    }
                    else if (current == "*") {
                        if (stackOper.tail->cell == "*") {
                            ProcessingExpression("*", stackOper, stackNumb, current, 0);
                        }
                        else {
                            stackOper.AddTail(current);
                        }
                    }

                }

                else if (current == "(") {
                    stackOper.AddTail(current);
                }
                else if (current.at(0) == '-') {
                    if (stackOper.tail != nullptr) {
                        if (stackOper.tail->cell == "-") {
                            int temp = stoi(current);
                            temp = temp * (-1);
                            string strTemp = to_string(temp);
                            stackNumb.AddTail(strTemp);
                            stackOper.tail->cell = "+";
                        }
                    }
                    stackNumb.AddTail(current);
                    continue;
                }
                else if (isdigit(current.at(0))) {
                    if (stackOper.tail != nullptr) {
                        if (stackOper.tail->cell == "-") {
                            int temp = stoi(current);
                            temp = temp * (-1);
                            string strTemp = to_string(temp);
                            stackNumb.AddTail(strTemp);
                            stackOper.tail->cell = "+";
                        }
                        else {
                            stackNumb.AddTail(current);
                        }
                    }
                    else {
                        stackNumb.AddTail(current);
                    }
                }
                else {
                    while (stackOper.tail->cell != "(") { 
                        string tempOper = stackOper.tail->cell;
                        int B = stoi(stackNumb.tail->cell);
                        stackNumb.DeleteTail();
                        int A = stoi(stackNumb.tail->cell);
                        stackNumb.DeleteTail();

                        int result = 0;
                        if (tempOper == "*")  result = A * B;
                        else if (tempOper == "+") result = A + B;
                        else if (tempOper == "-") result = A - B;

                        string temp = to_string(result);
                        stackNumb.AddTail(temp);

                        stackOper.DeleteTail();
                    }
                    stackOper.DeleteTail();

                    if (stackOper.tail != nullptr) {
                        if (stackOper.tail->cell == "-") {
                            int temp = stoi(stackNumb.tail->cell);
                            temp = temp * (-1);
                            string strTemp = to_string(temp);
                            stackNumb.tail->cell = strTemp;
                            stackOper.tail->cell = "+";
                        }
                    }

                }
            }

            while (stackOper.head != nullptr) {
                if (stackOper.head->next != nullptr) {
                    if ((stackOper.head->cell == "-" && stackOper.head->next->cell == "*") || (
                        (stackOper.head->cell == "+" && stackOper.head->next->cell == "*"))) {
                        string oper = stackOper.head->next->cell;

                        int b = stoi(stackNumb.head->next->next->cell);
                        int a = stoi(stackNumb.head->next->cell);

                        int result;
                        result = a * b;
                        string resultStr = to_string(result);

                        stackNumb.DelElementValue(stackNumb.head->next);
                        stackOper.DelElementValue(stackOper.head->next);

                        stackNumb.head->next->cell = resultStr;

                    }
                }
                string oper = stackOper.head->cell;
                stackOper.SPOP();

                int b = stoi(stackNumb.head->next->cell);
                int a = stoi(stackNumb.head->cell);
                stackNumb.SPOP();
                stackNumb.SPOP();

                int result;
                if (oper == "+") result = a + b;
                else if (oper == "-") result = a - b;
                else if (oper == "*") result = a * b;

                string resultStr = to_string(result);
                stackNumb.SPUSH(resultStr);

            }
            cout << endl << "Result: " << stackNumb.tail->cell << endl;

        } 
        else if (numberTask == "2") {
            SetNode set(15);
            string command;
            string commandWord;
            cout << endl << "Enter the command >>>> ";
            cin.ignore();
            getline(cin, command);
            stringstream ss(command);
            string fileName;
            string element;
            ss >> commandWord;
            ss >> fileName;
            ss >> element;

            ifstream FileRead(fileName + ".txt");
            string token;
            while (getline(FileRead, token, ' ')) {
                set.SETADD(token);
            }
            FileRead.close();
            if (commandWord == "SETADD") {
                set.SETADD(element);
            }
            else if (commandWord == "SETDEL") {
                set.SETDEL(element);
            }
            else if (commandWord == "SET_AT") {
                set.SET_AT(element);
                continue;
            }
            else {
                cout << endl << "Incorrect input!" << endl;
                continue;
            }
            ofstream FileWrite(fileName + ".txt");
            for (int i = 0; i < set.size; i++) {
                if (set.plenty[i] != nullptr && !set.plenty[i]->value.empty()) {
                    FileWrite << set.plenty[i]->value << " ";
                }
            }
            FileWrite.close();
        }
        else if (numberTask == "3") {
            SetNode set1(15);
            SetNode set2(15);

            string command1;
            cout << endl << "Select the first set >>>> ";
            cin.ignore();
            getline(cin, command1);
            stringstream ss1(command1);
            string fileName1;
            ss1 >> fileName1;

            string command2;
            cout << endl << "Select the second set >>>> ";
            getline(cin, command2);
            stringstream ss2(command2);
            string fileName2;
            ss2 >> fileName2;

            ifstream FileRead1(fileName1 + ".txt");
            string token1;
            while (getline(FileRead1, token1, ' ')) {
                set1.SETADD(token1);
            }
            FileRead1.close();
            ifstream FileRead2(fileName2 + ".txt");
            string token2;
            while (getline(FileRead2, token2, ' ')) {
                set2.SETADD(token2);
            }
            FileRead2.close();
            
            string command3;
            cout << endl << "Select operation >>>> ";
            getline(cin, command3);
            stringstream ss3(command3);
            string operation;
            string fileName3;
            ss3 >> operation;
            ss3 >> fileName3;

            if (operation == "SetUnion") {
                cout << endl;
                cout << "Result set: ";
                SetNode* unionSet = SetUnion(set1, set2);
                for (int i = 0; i < unionSet->size; i++) {
                    if (unionSet->plenty[i] != nullptr) {
                        cout << unionSet->plenty[i]->value << " ";
                    }
                }
                cout << endl;
                ofstream FileWrite(fileName3 + ".txt");
                for (int i = 0; i < unionSet->size; i++) {
                    if (unionSet->plenty[i] != nullptr && !unionSet->plenty[i]->value.empty()) {
                        FileWrite << unionSet->plenty[i]->value << " ";
                    }
                }
                FileWrite.close();
            } else if (operation == "SetIntersection"){
                cout << endl;
                cout << "Result set: ";
                SetNode* intersectionSet = SetIntersection(set1, set2);
                for (int i = 0; i < intersectionSet->size; i++) {
                    if (intersectionSet->plenty[i] != nullptr) {
                        cout << intersectionSet->plenty[i]->value << " ";
                    }
                }
                cout << endl;
                ofstream FileWrite(fileName3 + ".txt");
                for (int i = 0; i < intersectionSet->size; i++) {
                    if (intersectionSet->plenty[i] != nullptr && !intersectionSet->plenty[i]->value.empty()) {
                        FileWrite << intersectionSet->plenty[i]->value << " ";
                    }
                }
                FileWrite.close();
            } else if (operation == "SetDifference"){
                cout << endl;
                cout << "Result set: ";
                SetNode* diffSet = SetDifference(set1, set2);
                for (int i = 0; i < diffSet->size; i++) {
                    if (diffSet->plenty[i] != nullptr) {
                        cout << diffSet->plenty[i]->value << " ";
                    }
                }
                cout << endl;
                ofstream FileWrite(fileName3 + ".txt");
                for (int i = 0; i < diffSet->size; i++) {
                    if (diffSet->plenty[i] != nullptr && !diffSet->plenty[i]->value.empty()) {
                        FileWrite << diffSet->plenty[i]->value << " ";
                    }
                }
                FileWrite.close();
            } else {
                cout << endl << "Incorrect input!" << endl;
                continue;
            }
        }
        else if (numberTask == "4") {
            string command;
            cout << endl << "Input original string and pattern >>>> ";
            cin.ignore();
            getline(cin, command);
            stringstream ss(command);
            string str;
            string pattern;
            ss >> str;
            ss >> pattern;

            Array strArray;
            strArray.MPUSHfromString(str);
            Array patternArray;
            patternArray.MPUSHfromString(pattern);
            cout << endl;
            TestPatternMatch(strArray, patternArray);
        }
        else if (numberTask == "5"){
            Tree tree;
            int value;
            cout << endl;
            cout << "Enter numbers to insert into tree (enter -1 to complete): ";
            while (cin >> value) {
                if (value == -1) {
                    break; // Завершаем цикл, если встречен -1
                }
                tree.Insert(value); // Вставляем только валидные значения
            }
            cout << "Tree height: " << tree.TreeHeight() << endl;
        }
        else if (numberTask == "6") {
            string elements;
            string strA;
            string strB;
            cout << endl << "Input >>>> ";
            cin >> strA >> strB;
            if (isIsomorphic(strA, strB)) {
                cout << endl << "They are isomorphic!" << endl;
            }
            else {
                cout << endl << "They are not isomorphic!" << endl;
            }
        }
        else if (numberTask == "exit") {
            return 0;
        }
        else {
            cout << endl << "Incorrect input!" << endl;
            continue;
        }
    }
}