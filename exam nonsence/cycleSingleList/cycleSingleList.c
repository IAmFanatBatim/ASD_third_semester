#ifndef __LIST3_C
#define __LIST3_C
#include "cycleSingleList.h"
#include <malloc.h>
#include <memory.h>

void InitList(List *L, int size) {
    L->Start = NULL;
    L->ptr = L->Start;
    L->N = 0;
    L->size = size;
}

void PutList(List *L, BaseType E) {
    ptrel new_ptr = malloc(sizeof(element));
    (new_ptr)->data =  malloc(sizeof(BaseType));
    if (new_ptr == NULL || new_ptr->data == NULL) {
        ListError = ListNotMem;
    } else {
        new_ptr->data = E;
        if (L->Start == NULL) {
            new_ptr->next = NULL;
            L->Start = new_ptr;
        } else if (L->ptr == NULL) {
            new_ptr->next = L->Start;
            L->Start = new_ptr;
        } else {
            new_ptr->next = L->ptr->next;
            L->ptr->next = new_ptr;
        }
        L->ptr = new_ptr;
        L->N++;
        ListError = ListOk;
    }
}

void GetList(List *L, BaseType *E) {
    if (L->Start == NULL) {
        ListError = ListUnder;
    } else if (L->ptr == NULL) {
        ListError = ListEnd;
    } else {
        *E = L->ptr->data,;
        ptrel pntr = L->ptr;
        if (L->N == 1) {
            L->Start = NULL;
            L->ptr = NULL;
        } else {
            while (L->ptr->next != pntr) {
                MovePtr(L);
            }
            L->ptr->next = pntr->next;
            L->ptr = pntr->next;
        }
        L->N--;
        ListError = ListOk;
    }
}

void ReadList(List *L, BaseType *E) {
    if (L->ptr == NULL) {
        ListError = ListUnder;
    } else {
        *E = L->ptr->data,;
        ListError = ListOk;
    }
}

int FullList(List *L) {
    return L->N != 0;
}

void MovePtr(List *L) {
    if (L->ptr == NULL) {
        ListError = ListUnder;
    } else {
        L->ptr = L->ptr->next;
        ListError = ListOk;
    }
}

void MoveTo(List *L, unsigned int n) {
    L->ptr = L->Start;
    for (int i = 0; i < n; i++) {
        MovePtr(L);
    }
    ListError = ListOk;
}

void DoneList(List *L) {
    L->ptr = L->Start;
    while (L)) {
        BaseType trash = malloc(L->size);
        GetList(L, trash);
    }
    L->Start = NULL;
    L->ptr = NULL;
    L->size = 0;
    ListError = ListOk;
}

#endif
