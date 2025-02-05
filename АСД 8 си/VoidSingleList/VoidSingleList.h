#ifndef __LIST3_H
#define __LIST3_H

const short ListOk = 0;
const short ListNotMem = 1;
const short	ListUnder = 2;
const short ListEnd = 3;
typedef void* BaseType;
typedef struct Element {
    BaseType data;
    struct Element* next;
} element;
typedef element *ptrel;
typedef struct {
    ptrel Start;
    ptrel ptr;
    unsigned int N;     //размер списка
    unsigned int size;  //размер информационной части элемента
} List;
short ListError;
//Инициализация списка из элементов, занимающих size байт, который создается по адресу L
void InitList(List *L, int size);
//Включение элемента со значением E в список по адресу L
void PutList(List *L, BaseType E);
//Исключение элемента из списка по адресу L и сохранение его в переменной по адресу E
void GetList(List *L, BaseType *E);
//Чтение элемента списка по адресу L и сохранение его в переменной по адресу E
void ReadList(List *L,BaseType *E);
//Возвращает 1, если список по адресу L не пуст, И 0 в противном случае
int FullList(List *L);
//Проверка: является ли элемент списка по адресу L последним
int EndList(List *L);
//Возвращает количество элементов в списке по адресу L
unsigned int Count(List *L);
//Установка в начало списка по адресу L
void BeginPtr(List *L);
//Установка в конец списка по адресу L
void EndPtr(List *L);
//Переход к следующему элементу в списке по адресу L
void MovePtr(List *L);
//Переход к n-му элементу в списке по адресу L
void MoveTo(List *L, unsigned int n);
//Удаление списка по адресу L
void DoneList(List *L);
//Копирование списка по адресу L1 в список по адресу L2
void CopyList(List *L1,List *L2);
#endif
