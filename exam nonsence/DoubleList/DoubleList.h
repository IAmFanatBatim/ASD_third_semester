#ifndef __DList3_H
#define __DList3_H

const short DListOk = 0;
const short DListNotMem = 1;
const short	DListEmpty = 2;
const short DListPtrB = 3;
const short DListPtrE = 4;
typedef int BaseType;
typedef struct Element {
    BaseType data;
    struct Element* next;
    struct Element* prev;
} element;
typedef element *ptrel;
typedef struct {
    ptrel Start;
    ptrel End;
    ptrel ptr;
    unsigned int N;     //размер списка
} DList;
short DListError;
void InitDList(DList *L, int size);
void PutPred(DList *L, BaseType E);
void PutPost(DList *L, BaseType E);
void GetPred(DList *L, BaseType *E);
void GetPost(DList *L, BaseType *E);
int EmptyDList(DList *L);
void MovePtrL(DList *L);
void MovePtrR(DList *L);
void DoneDList(DList *L);
#endif
