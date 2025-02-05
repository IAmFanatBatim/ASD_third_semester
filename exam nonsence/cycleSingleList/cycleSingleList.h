#ifndef __LIST3_H
#define __LIST3_H

const short ListOk = 0;
const short ListNotMem = 1;
const short	ListUnder = 2;
typedef int BaseType;
typedef struct Element {
    BaseType data;
    struct Element* next;
} element;
typedef element *ptrel;
typedef struct {
    ptrel Start;
    ptrel ptr;
    unsigned int N;     //размер списка
} List;
short ListError;
void InitList(List *L, int size);
void PutList(List *L, BaseType E);
void GetList(List *L, BaseType *E);
void ReadList(List *L,BaseType *E);
int FullList(List *L);
void MovePtr(List *L);
void MoveTo(List *L, unsigned int n);
void DoneList(List *L);
#endif
