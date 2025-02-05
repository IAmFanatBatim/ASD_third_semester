#ifndef __TABLE1_H
#define __TABLE1_H
#include "../VoidSingleList/VoidSingleList.h" // Cмотреть лаб.раб. №5

const short TableOk = 0;
const short TableNotMem = 1;
const short TableUnder = 2;
int TableError; // 0..2

typedef List Table;
typedef char T_Key[16]; // Определить тип ключа

//Сравнивает ключи элементов таблицы, адреса которых находятся в параметрах a и b.
//Возвращает -1, если ключ элемента по адресу a меньше ключа элемента по адресу b,
// 0 — если ключи равны и +1 — если ключ элемента по адресу a больше ключа элемента по адресу b
typedef int (* func)(void*, void*);

void InitTable(Table *T, unsigned SizeEl);
//Возвращает 1, если таблица пуста, иначе — 0
int EmptyTable(Table *T);
//Включение элемента в таблицу. Возвращает 1 , если элемент включен в таблицу, иначе — 0
//(Если в таблице уже есть элемент с заданным ключем или не хватает памяти)
int PutTable(Table *T, void *E, func f);
//Исключение элемента. Возвращает 1 , если элемент с ключем Key  был в таблице, иначе — 0
int GetTable(Table *T, void *E,  T_Key Key, func f);
//Чтение элемента. Возвращает 1 , если элемент с ключем Key есть в таблице, иначе — 0
int ReadTable(Table *T, void *E, T_Key Key, func f);
//Изменение элемента. Возвращает 1 , если элемент с ключем Key есть в таблице, иначе — 0
int WriteTable(Table *T, void *E, T_Key Key, func f);
//Удаление таблицы из динамической памяти
void DoneTable(Table *T);

#endif