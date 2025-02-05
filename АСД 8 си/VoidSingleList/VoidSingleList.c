#ifndef __LIST3_C
#define __LIST3_C
#include "VoidSingleList.h"
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
    (new_ptr)->data =  malloc(L->size);
    if (new_ptr == NULL || new_ptr->data == NULL) {
        ListError = ListNotMem;
    } else {
        memcpy(new_ptr->data, E, L->size);
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
        memcpy(E, L->ptr->data, L->size);
        ptrel pntr = L->ptr;

        if (pntr == L->Start) {
            L->Start = pntr->next;
        } else {
            BeginPtr(L);
            while (L->ptr->next != pntr) {
                MovePtr(L);
            }
            L->ptr->next = pntr->next;
        }
        L->ptr = pntr->next;
        free(pntr->data);
        free(pntr);
        L->N--;
        ListError = ListOk;
    }
}

void ReadList(List *L, BaseType *E) {
    if (L->ptr == NULL) {
        ListError = ListUnder;
    } else {
        memcpy(E, L->ptr->data, L->size);
        ListError = ListOk;
    }
}

int FullList(List *L) {
    return L->N != 0;
}

int EndList(List *L) {
    return (L->ptr)->next == NULL;
}

unsigned int Count(List *L) {
    return L->N;
}

void BeginPtr(List *L) {
    L->ptr = L->Start;
}

void EndPtr(List *L) {
    BeginPtr(L);
    for (int i = 1; i < L->N; i++) {
        MovePtr(L);
    }
}

void MovePtr(List *L) {
    if (L->ptr == NULL) {
        ListError = ListEnd;
    } else {
        L->ptr = L->ptr->next;
        ListError = ListOk;
    }
}

void MoveTo(List *L, unsigned int n) {
    BeginPtr(L);
    if (n > L->N) {
        ListError = ListEnd;
    } else {
        for (int i = 0; i < n; i++) {
            MovePtr(L);
        }
        ListError = ListOk;
    }
}

void DoneList(List *L) {
    BeginPtr(L);
    while (FullList(L)) {
        BaseType trash = malloc(L->size);
        GetList(L, trash);
    }
    L->Start = NULL;
    L->ptr = NULL;
    L->size = 0;
    ListError = ListOk;
}

void CopyList(List *L1, List *L2) {
    ptrel ptr_value = L1->ptr;
    BeginPtr(L1);
    BeginPtr(L2);
    while (L2->Start != 0) {
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

#endif
