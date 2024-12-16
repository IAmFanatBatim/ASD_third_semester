#include "tree.h"
#include "tree.c"

#include <stdio.h>
#include <ctype.h>

int add(int x, int y) {
    return x + y;
}
int subtract(int x, int y) {
    return x - y;
}
int multiply(int x, int y) {
    return x * y;
}
int divide(int x, int y) {
    return x / y;
}

//Массив символов, обозначающих операции сложения, вычитания, умножения, деления нацело
char marks[4] = {'+', '-', '*', '/'};
//Массив функций, выполняющих операции сложение, вычитание, умножение, деление нацело двух целых чисел
int (*operations[4]) (int, int)  = {add, subtract, multiply, divide};

//Возвращает числовой код операции (0, 1, 2, 3) по символу, обозначающему этому операцию
int getCodeByMark(char marking) {
    for (int i = 0; i < 4; i++) {
        if (marks[i] == marking) {
            return i;
        }
    }
    return -1;
}

//Строит дерево арифметического выражения, заданного в ППЗ. Операнды — целочисленные константы.
//Операции — «+», «–», «*» и «div».
void BildTree(Tree *T) {
    char cur_sym = getchar();
    if (cur_sym == '+' || cur_sym == '-' || cur_sym == '*' || cur_sym == '/') {
        char next_sym = getchar();
        if (cur_sym != '-' || isspace(next_sym)) {
            WriteDataTree(T, getCodeByMark(cur_sym));
            Tree TL, TR;
            InitTree(&TL);
            InitTree(&TR);
            MoveToLSon(T, &TL);
            CreateRoot(&TL);
            WriteDataTree(&TL, 0);
            BildTree(&TL);
            MoveToRSon(T, &TR);
            CreateRoot(&TR);
            WriteDataTree(&TR, 0);
            BildTree(&TR);
        }
        else {
            int cur_value = -(next_sym - '0');
            WriteDataTree(T, cur_value);
            BildTree(T);
        }
    } else if (cur_sym >= '0' && cur_sym <= '9') {
        while(!isspace(cur_sym)) {
            int cur_value;
            ReadDataTree(T, &cur_value);
            cur_value = cur_value * 10 + (cur_sym - '0') * ((cur_value < 0) ? -1 : 1);
            WriteDataTree(T, cur_value);
            cur_sym = getchar();
        }
    }
}

//Выводит арифметическое выражение в ОПЗ.
void WritePostfix(Tree *T) {
    if (IsLSon(T)) {
        Tree TL, TR;
        InitTree(&TL);
        InitTree(&TR);
        MoveToLSon(T, &TL);
        WritePostfix(&TL);
        MoveToRSon(T, &TR);
        WritePostfix(&TR);
        int value;
        ReadDataTree(T, &value);
        printf("%c ", marks[value]);
    } else {
        int value;
        ReadDataTree(T, &value);
        printf("%d ", value);
    }
}

//Вычисляет значение по дереву арифметического выражения и выводит результат выполнения каждой операции в виде:
//<операнд><операция><операнд>=<значение>
int WriteCalc(Tree *T) {
    if (IsLSon(T)) {
        Tree TL, TR;
        InitTree(&TL);
        InitTree(&TR);
        MoveToLSon(T, &TL);
        int first = WriteCalc(&TL);
        MoveToRSon(T, &TR);
        int second = WriteCalc(&TR);
        int op;
        ReadDataTree(T, &op);
        printf("%d %c %d = %d\n", first, marks[op], second, operations[op](first, second));
        return operations[op](first, second);
    } else {
        int value;
        ReadDataTree(T, &value);
        return value;
    }
}

int main() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    BildTree(&T);
    WritePostfix(&T);
    printf("\n");
    WriteCalc(&T);
}