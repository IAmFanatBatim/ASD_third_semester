#ifndef __DList3_C
#define __DList3_C
#include "DoubleList.h"
#include <malloc.h>
#include <memory.h>

void InitDList(DList *L, int size) {
    L->Start = NULL;
    L->End = NULL;
    L->ptr = L->Start;
    L->N = 0;
    L->size = size;
}

void PutPred(DList *L, BaseType E) {
    ptrel new_ptr = malloc(sizeof(element));
    (new_ptr)->data = malloc(sizeof(BaseType));
    if (new_ptr == NULL || new_ptr->data == NULL) {
        DListError = DListNotMem;
    } else if (L->ptr == L->Start) {
        DListError = DListPtrB;
    } else {
        new_ptr->data = E;
        if (L->Start == NULL) {
            new_ptr->next = NULL;
            L->Start = new_ptr;
            L->End = new_ptr;
        } else {
            new_ptr->next = L->ptr->next;
            new_ptr->prev = L->ptr->prev;
            L->ptr->prev = new_ptr;
        }
        L->ptr = new_ptr;
        L->N++;
        DListError = DListOk;
    }
}

void PutPost(DList *L, BaseType E) {
    ptrel new_ptr = malloc(sizeof(element));
    (new_ptr)->data = malloc(sizeof(BaseType));
    if (new_ptr == NULL || new_ptr->data == NULL) {
        DListError = DListNotMem;
    } else if (L->ptr == L->End) {
        DListError = DListPtrE;
    } else {
        new_ptr->data = E;
        if (L->Start == NULL) {
            new_ptr->next = NULL;
            L->Start = new_ptr;
            L->End = new_ptr;
        } else {
            new_ptr->next = L->ptr->next;
            new_ptr->prev = L->ptr->prev;
            L->ptr->prev = new_ptr;
        }
        L->ptr = new_ptr;
        L->N++;
        DListError = DListOk;
    }
}

void GetDList(DList *L, BaseType *E) {
    if (L->Start == NULL) {
        DListError = DListUnder;
    } else if (L->ptr == NULL) {
        DListError = DListEnd;
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
        DListError = DListOk;
    }
}

void ReadDList(DList *L, BaseType *E) {
    if (L->ptr == NULL) {
        DListError = DListUnder;
    } else {
        memcpy(E, L->ptr->data, L->size);
        DListError = DListOk;
    }
}

int FullDList(DList *L) {
    return L->N != 0;
}

int EndDList(DList *L) {
    return (L->ptr)->next == NULL;
}

unsigned int Count(DList *L) {
    return L->N;
}

void BeginPtr(DList *L) {
    L->ptr = L->Start;
}

void EndPtr(DList *L) {
    BeginPtr(L);
    for (int i = 1; i < L->N; i++) {
        MovePtr(L);
    }
}

void MovePtr(DList *L) {
    if (L->ptr == NULL) {
        DListError = DListEnd;
    } else {
        L->ptr = L->ptr->next;
        DListError = DListOk;
    }
}

void MoveTo(DList *L, unsigned int n) {
    BeginPtr(L);
    if (n > L->N) {
        DListError = DListEnd;
    } else {
        for (int i = 0; i < n; i++) {
            MovePtr(L);
        }
        DListError = DListOk;
    }
}

void DoneDList(DList *L) {
    BeginPtr(L);
    while (FullDList(L)) {
        BaseType trash = malloc(L->size);
        GetDList(L, trash);
    }
    L->Start = NULL;
    L->ptr = NULL;
    L->size = 0;
    DListError = DListOk;
}

void CopyDList(DList *L1, DList *L2) {
    ptrel ptr_value = L1->ptr;
    BeginPtr(L1);
    BeginPtr(L2);
    while (L2->Start != 0) {
        BaseType trash;
        GetDList(L2, &trash);
    }
    for (int i = 0; i < L1->N; i++) {
        BaseType cur_data;
        ReadDList(L1, &cur_data);
        PutDList(L2, cur_data);
        MovePtr(L1);
    }
    L1->ptr = ptr_value;
    DListError = DListOk;
}

#endif
