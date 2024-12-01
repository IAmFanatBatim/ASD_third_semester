#if !defined(__LIST5_C)
#define __LIST5_C
#include "List.h"

#include <stdlib.h>
#include <stdio.h>


void InitList(List *L) {
     L->start = 0;
     L->ptr = 0;
     L->N = 0;
}

void PutList(List *L, BaseType E) {
    if (EmptyMem()) {
        ListError = ListNotMem;
        exit(ListError);
    } else {
        ptrel pntr = NewMem();
        MemList[pntr].data = E;
        if (L->start == 0) {
            MemList[pntr].next = 0;
            L->start = pntr;
        } else if (L->ptr == 0) {
            MemList[pntr].next = L->start;
            L->start = pntr;
        } else {
            MemList[pntr].next = MemList[L->ptr].next;
            MemList[L->ptr].next = pntr;
        }
        L->ptr = pntr;
        L->N++;
        ListError = ListOk;
    }
}

void GetList(List *L, BaseType *E)  {
    if (L->start == 0) {
        ListError = ListUnder;
        exit(ListError);
    } else if (L->ptr == 0) {
        ListError = ListEnd;
        exit(ListError);
    } else {
        *E = MemList[L->ptr].data;
        ptrel pntr = L->ptr;
        if (pntr == L->start) {
            L->start = MemList[pntr].next;
        } else {
            BeginPtr(L);
            while (MemList[L->ptr].next != pntr) {
                MovePtr(L);
            }
            MemList[L->ptr].next = MemList[pntr].next;
        }
        L->ptr = MemList[pntr].next;
        DisposeMem(pntr);
        L->N--;
        ListError = ListOk;
    }
}

void ReadList(List *L,BaseType *E) {
    if (L->ptr == 0) {
        ListError = ListUnder;
        exit(ListError);
    }
    *E = MemList[L->ptr].data;
    ListError = ListOk;
}

int FullList(List *L) {
    return L->start != 0;
}

int EndList(List *L) {
    if (L->ptr == 0) {
        ListError = ListEnd;
        exit(ListError);
    }
    ListError = ListOk;
    return MemList[L->ptr].next == 0;
}

unsigned int Count(List *L) {
    return L->N;
}

void BeginPtr(List *L) {
    L->ptr = L->start;
}

void EndPtr(List *L) {
    BeginPtr(L);
    for (int i = 1; i < L->N; i++) {
        MovePtr(L);
    }
}

void MovePtr(List *L) {
    if (L->ptr == 0) {
        ListError = ListEnd;
        exit(ListError);
    }
    L->ptr = MemList[L->ptr].next;
    ListError = ListOk;
}

void MoveTo(List *L, unsigned int n) {
    BeginPtr(L);
    if (n > L->N) {
        ListError = ListEnd;
        exit (ListError);
    }
    for (int i = 0; i < n; i++) {
        MovePtr(L);
    }
    ListError = ListOk;
}

void DoneList(List *L) {
    BeginPtr(L);
    if (FullList(L)) {
        while ((MemList[L->ptr].next) != 0) {
            BaseType trash;
            GetList(L, &trash);
        }
    }
    free(L);
}

void CopyList(List *L1,List *L2) {
    ptrel ptr_value = L1->ptr;
    BeginPtr(L1);
    BeginPtr(L2);
    while (L2->start != 0) {
        BaseType trash;
        GetList(L2, &trash);
    }
    for (int i = 0; i < L1->N; i++) {
        BaseType cur_data;
        ReadList(L1, &cur_data);
        PutList(L2, cur_data);
        MovePtr(L1);
    }
    L1->ptr = ptr_value;
    ListError = ListOk;
}

void InitMem() {
    for (int i = 0; i < SizeList-1; i++) {
        MemList[i].next = i+1;
    }
    MemList[SizeList-1].next = 0;
}

int EmptyMem() {
    return MemList[0].next == 0;
}

unsigned NewMem() {
    ptrel first_free = MemList[0].next;
    MemList[0].next = MemList[first_free].next;
    return first_free;
}

void DisposeMem(unsigned n) {
    ptrel first_free = MemList[0].next;
    MemList[0].next = n;
    MemList[n].next = first_free;
}

int IsProgression (List *P, int h) {
    BeginPtr(P);
    int x0;
    ReadList(P, &x0);
    for (int i = 1; i < P->N; i++) {
        int x;
        MovePtr(P);
        ReadList(P, &x);
        if (x != x0 + h*i) {
            return 0;
        }
    }
    ListError = ListOk;
    return 1;
}

#endif