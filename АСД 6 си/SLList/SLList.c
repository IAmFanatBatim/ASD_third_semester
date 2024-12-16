#ifndef __LIST6_C
#define __LIST6_C
#include "SLList.h"
#include <malloc.h>
#include <memory.h>

void InitList(List *L, unsigned Size){
    for (int i = 0; i < SizeList; i++) {
        L->MemList[i] = malloc(Size);
    }
    L->ptr = 0;
    L->N = 0;
    L->Size = Size;
}

void PutList(List *L, BaseType E){
    if (L->N == L->Size) {
        ListError = ListNotMem;
        exit(ListError);
    } else if (L->ptr > L->N) {
        ListError = ListEnd;
        exit(ListError);
    } else {
        for (ptrel cur_el = L->N; cur_el > L->ptr; cur_el--) {
            memcpy(L->MemList[cur_el], L->MemList[cur_el - 1], L->Size);
        }
        memcpy(L->MemList[L->ptr], E, L->Size);
        L->ptr += 1;
        L->N += 1;
        ListError = ListOk;
    }
}

void GetList(List *L, BaseType *E) {
    if (L->N == 0) {
        ListError = ListUnder;
        exit(ListError);
    } else if (L->ptr > L->N || L->ptr == 0) {
        ListError = ListEnd;
        exit(ListError);
    } else {
        memcpy(E, L->MemList[L->ptr-1], L->Size);
        for (ptrel cur_el = L->ptr-1; cur_el < L->N - 1; cur_el++) {
            L->MemList[cur_el] = L->MemList[cur_el + 1];
        }
        L->ptr--;
        L->N -= 1;
        ListError = ListOk;
    }
}

void ReadList(List *L, BaseType *E) {
    if (L->N == 0) {
        ListError = ListUnder;
        exit(ListError);
    } else if (L->ptr > L->N || L->ptr == 0) {
        ListError = ListEnd;
        exit(ListError);
    } else {
        memcpy(E, L->MemList[L->ptr-1], L->Size);
        ListError = ListOk;
    }
}

int FullList(List *L) {
    return L->N != 0;
}

int EndList(List *L) {
    return L->ptr == L->N;
}

unsigned int Count(List *L) {
    return L->N;
}

void BeginPtr(List *L) {
    if (L->N == 0) {
        L->ptr = 0;
    } else {
        L->ptr = 1;
    }
}

void EndPtr(List *L) {
    L->ptr = L->N;
}

void MovePtr(List *L) {
    L->ptr += 1;
}

void MoveTo(List *L, unsigned int n) {
    L->ptr = n;
}

void DoneList(List *L) {
    L->N = 0;
    L->Size = 0;
    L->ptr = 0;
}

void CopyList(List *L1, List *L2) {
    for (ptrel cur_el = 0; cur_el < L1->N; cur_el++) {
        memcpy(L2->MemList[cur_el], L1->MemList[cur_el], L1->Size);
    }
    L2->N = L1->N;
    if (L2->ptr > L2->N) {
        L2->ptr =  L2->N - 1;
    }
    ListError = ListOk;
}

#endif
