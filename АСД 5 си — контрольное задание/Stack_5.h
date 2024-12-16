#ifndef __STACK_5_H
#define __STACK_5_H
#include "../АСД 5 си/list.h"

const short StackOk = ListOk;
const short StackUnder = ListUnder;
const short StackOver = ListNotMem;
int StackError; // Переменная ошибок
typedef List Stack;

// Инициализация стека по адресу s
void InitStack(Stack *s);
//Поместить элемент со значением E в стек по адресу s
void PutStack(Stack *s, BaseType E);
//Извлечь элемент из стека по адресу s в переменную по адресу E
void GetStack(Stack *s, BaseType *E);
// Проверка, пуст ли стек по адресу s
int  EmptyStack(Stack *s);
//Прочитать элемент из вершины стека по адресу s и сохранить в переменную по адресу E
void ReadStack(Stack *s, BaseType *E);
//Уничтожить стек по адресу s
void DoneStack(Stack *s);

#endif
