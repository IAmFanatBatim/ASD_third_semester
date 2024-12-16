#ifndef __STACK10_H
#define __STACK10_H
#include "../SLList/SLList.h"
const short StackOk = ListOk;
const short StackUnder = ListUnder;
const short StackOver = ListNotMem;
short StackError; // Переменная ошибок

typedef List Stack;
//Инициализация стека с максимлаьным размером size по адресу s
void InitStack(Stack *s, unsigned Size);
//Поместить элемент из переменной по адресу E в стек по адресу s
void PutStack(Stack *s, void *E);
//Извлечь элемент из стека по адресу s в переменную по адресу E
void GetStack(Stack *s, void *E);
//Проверка: пуст и стек по адресу s
int EmptyStack(Stack s);
//Прочитать элемент из вершины стека, записать в переменную по адресу E
void ReadStack(Stack s, void *E);
//Уничтожить стек по адресу s
void DoneStack(Stack *s);
		
#endif