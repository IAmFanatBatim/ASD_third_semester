#ifndef __TABLE1_C
#define __TABLE1_C
#include "../VoidSingleList/VoidSingleList.c" // Cмотреть лаб.раб. №5
#include "Table.h"

void InitTable(Table *T, unsigned SizeEl) {
    InitList(T, SizeEl + sizeof(T_Key));
}

int EmptyTable(Table *T) {
    return !FullList(T);
}

int PutTable(Table *T, void *E, func f) {
    BeginPtr(T);
    for (int cur_ind = 1; cur_ind <= T->N; cur_ind++) {
        if (f(T->ptr->data, E) == 0) {
            return 0;
        }
        if (cur_ind < T->N) {
            MovePtr(T);
        }
    }
    PutList(T, E);
    //TableError = ListError;
    //if (TableError == 1) {
      //  exit (TableError);
   // }
    return 1;
}

int GetTable(Table *T, void *E, T_Key Key, func f) {
    BeginPtr(T);
    for (int cur_ind = 1; cur_ind <= T->N; cur_ind++) {
        if (f(T->ptr->data, Key) == 0) {
            GetList(T, E);
            return 1;
        }
        MovePtr(T);
    }
    return 0;
}

int ReadTable(Table *T, void *E, T_Key Key, func f) {
    BeginPtr(T);
    for (int cur_ind = 1; cur_ind <= T->N; cur_ind++) {
        if (f(T->ptr->data, Key) == 0) {
            ReadList(T, E);
            return 1;
        }
        MovePtr(T);
    }
    return 0;
}

int WriteTable(Table *T, void *E, T_Key Key, func f) {
    BeginPtr(T);
    for (int cur_ind = 1; cur_ind <= T->N; cur_ind++) {
        if (f(T->ptr->data, Key) == 0) {
            memcpy(T->ptr->data, E, T->size);
            return 1;
        }
        MovePtr(T);
    }
    return 0;
}

void DoneTable(Table *T) {
    DoneList(T);
}

#endif