#include "List.h"
#include "List.c"

#include <stdio.h>
#include <assert.h>


void Test_InitList() {
    List L;
    InitList(&L);
    assert(L.start == 0 && L.ptr == 0 && L.N == 0);
}

void Test_PutList_InEmpty() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    assert(MemList[L.start].data == 5 && MemList[L.ptr].data == 5 && MemList[L.ptr].next == 0 &&L.N == 1);
}
void Test_PutList_AtEnd() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    assert(MemList[L.start].data == 5 && MemList[L.ptr].data == 7 && MemList[MemList[L.start].next].data == 7);
    assert(MemList[L.start].next == L.ptr && MemList[L.ptr].next == 0 && L.N == 2);
}
void Test_PutList_AtBeginning() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    L.ptr = 0;
    PutList(&L, 7);
    assert(MemList[L.start].data == 7 && MemList[L.ptr].data == 7 && MemList[MemList[L.start].next].data == 5);
    assert(L.start == L.ptr && MemList[MemList[L.ptr].next].next == 0 && L.N == 2);
}
void Test_PutList_Between() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_at_first = L.ptr;
    PutList(&L, 7);
    L.ptr = ptr_at_first;
    PutList(&L, 4);
    assert(MemList[L.start].data == 5 && MemList[L.ptr].data == 4 && MemList[MemList[L.start].next].data == 4);
    assert(MemList[MemList[L.ptr].next].data == 7 && MemList[MemList[L.ptr].next].next == 0 && L.N == 3);
}
void Test_PutList() {
    Test_PutList_InEmpty();
    Test_PutList_AtEnd();
    Test_PutList_AtBeginning();
    Test_PutList_Between();
}

void Test_GetList_OneAndOnly() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    BaseType container;
    GetList(&L, &container);
    assert(container == 5 && L.start == 0 && L.ptr == 0 && L.N == 0);
}
void Test_GetList_AtEnd() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    BaseType container;
    GetList(&L, &container);
    assert(container == 7 && MemList[L.start].data == 5);
    assert(L.ptr == 0 && MemList[L.start].next == 0 && L.N == 1);
}
void Test_GetList_AtBeginning() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_at_first = L.ptr;
    PutList(&L, 7);
    L.ptr = ptr_at_first;
    BaseType container;
    GetList(&L, &container);
    assert(container == 5 && MemList[L.start].data == 7 && MemList[L.ptr].data == 7);
    assert(MemList[L.start].next == 0 && MemList[L.ptr].next == 0 && L.N == 1);
}
void Test_GetList_Between() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_at_second = L.ptr;
    PutList(&L, 4);
    L.ptr = ptr_at_second;
    BaseType container;
    GetList(&L, &container);
    assert(container == 7 && MemList[L.start].data == 5 && MemList[L.ptr].data == 4 && MemList[MemList[L.start].next].data == 4);
    assert(MemList[L.ptr].next == 0 && L.N == 2);
}
void Test_GetList() {
    Test_GetList_OneAndOnly();
    Test_GetList_AtEnd();
    Test_GetList_AtBeginning();
    Test_GetList_Between();
}

void Test_ReadList_OneAndOnly() {
    List L;
    PutList(&L, 5);
    BaseType container;
    ReadList(&L, &container);
    assert(container == 5 && MemList[L.ptr].data == 5);
}
void Test_ReadList_AtEnd() {
    List L;
    PutList(&L, 5);
    PutList(&L, 7);
    BaseType container;
    ReadList(&L, &container);
    assert(container == 7 && MemList[L.ptr].data == 7);
}
void Test_ReadList_AtBeginning() {
    List L;
    PutList(&L, 5);
    ptrel ptr_at_first = L.ptr;
    PutList(&L, 7);
    L.ptr = ptr_at_first;
    BaseType container;
    ReadList(&L, &container);
    assert(container == 5 && MemList[L.ptr].data == 5);
}
void Test_ReadList_Between() {
    List L;
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_at_second = L.ptr;
    PutList(&L, 4);
    L.ptr = ptr_at_second;
    BaseType container;
    ReadList(&L, &container);
    assert(container == 7 && MemList[L.ptr].data == 7);
}
void Test_ReadList() {
    Test_ReadList_OneAndOnly();
    Test_ReadList_AtEnd();
    Test_ReadList_AtBeginning();
    Test_ReadList_Between();
}

void Test_FullList_Empty() {
    List L;
    InitList(&L);
    assert(!FullList(&L));
}
void Test_FullList_SomeElementsIn() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    assert(FullList(&L));
}
void Test_FullList_PtrAt0() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    L.ptr = 0;
    assert(FullList(&L));
}
void Test_FullList() {
    Test_FullList_Empty();
    Test_FullList_SomeElementsIn();
    Test_FullList_PtrAt0();
}

void Test_EndList_OneElement() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    assert(EndList(&L));
}
void Test_EndList_PtrAtEnd() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    assert(EndList(&L));
}
void Test_EndList_PtrInMiddle() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_at_second = L.ptr;
    PutList(&L, 4);
    L.ptr = ptr_at_second;
    assert(!EndList(&L));
}

void Test_EndList() {
    Test_EndList_OneElement();
    Test_EndList_PtrAtEnd();
    Test_EndList_PtrInMiddle();
}

void Test_Count_Empty() {
    List L;
    InitList(&L);
    assert(Count(&L) == 0);
}
void Test_Count_OneElement() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    assert(Count(&L) == 1);
}
void Test_Count_SomeElements() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    assert(Count(&L) == 3);
}
void Test_Count() {
    Test_Count_Empty();
    Test_Count_OneElement();
    Test_Count_SomeElements();
}

void Test_BeginPtr_Empty() {
    List L;
    InitList(&L);
    BeginPtr(&L);
    assert(L.ptr == 0);
}
void Test_BeginPtr_OneElement() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_start = L.ptr;
    BeginPtr(&L);
    assert(L.ptr == ptr_start);
}
void Test_BeginPtr_SomeElements() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_start = L.ptr;
    PutList(&L, 7);
    PutList(&L, 4);
    BeginPtr(&L);
    assert(L.ptr == ptr_start);
}
void Test_BeginPtr() {
    Test_BeginPtr_Empty();
    Test_BeginPtr_OneElement();
    Test_BeginPtr_SomeElements();
}

void Test_EndPtr_Empty() {
    List L;
    InitList(&L);
    BeginPtr(&L);
    assert(L.ptr == 0);
}
void Test_EndPtr_OneElement() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_end = L.ptr;
    EndPtr(&L);
    assert(L.ptr == ptr_end);
}
void Test_EndPtr_SomeElements() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    ptrel ptr_end = L.ptr;
    BeginPtr(&L);
    EndPtr(&L);
    assert(L.ptr == ptr_end);
}
void Test_EndPtr() {
    Test_EndPtr_Empty();
    Test_EndPtr_OneElement();
    Test_EndPtr_SomeElements();
}

void Test_MovePtr_OneElementTo0() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    MovePtr(&L);
    assert(L.ptr == 0);
}
void Test_MovePtr_SomeElementsTo0() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    MovePtr(&L);
    assert(L.ptr == 0);
}
void Test_MovePtr_SomeElementsFromFirst() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_second = L.ptr;
    PutList(&L, 4);
    BeginPtr(&L);
    MovePtr(&L);
    assert(L.ptr == ptr_second);
}
void Test_MovePtr_SomeElementsToLast() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    ptrel ptr_last = L.ptr;
    BeginPtr(&L);
    MovePtr(&L);
    MovePtr(&L);
    assert(L.ptr == ptr_last);
}
void Test_MovePtr() {
    Test_MovePtr_OneElementTo0();
    Test_MovePtr_SomeElementsTo0();
    Test_MovePtr_SomeElementsFromFirst();
    Test_MovePtr_SomeElementsToLast();
}

void Test_MoveTo_OneElement() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_first = L.ptr;
    L.ptr = 0;
    MoveTo(&L, 0);
    assert(L.ptr == ptr_first);
}
void Test_MoveTo_SomeElementsToFirst() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    ptrel ptr_first = L.ptr;
    PutList(&L, 7);
    PutList(&L, 4);
    MoveTo(&L, 0);
    assert(L.ptr == ptr_first);
}
void Test_MoveTo_SomeElementsToMiddle() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_second = L.ptr;
    PutList(&L, 4);
    MoveTo(&L, 1);
    assert(L.ptr == ptr_second);
}
void Test_MoveTo_SomeElementsToLast() {
    List L;
    InitList(&L);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    ptrel ptr_last = L.ptr;
    BeginPtr(&L);
    MoveTo(&L, 2);
    assert(L.ptr == ptr_last);
}
void Test_MoveTo() {
    Test_MoveTo_OneElement();
    Test_MoveTo_SomeElementsToFirst();
    Test_MoveTo_SomeElementsToMiddle();
    Test_MoveTo_SomeElementsToLast();
}

void Test_CopyList_Empty() {
    List L1, L2;
    InitList(&L1);
    InitList(&L2);
    CopyList(&L1, &L2);
    assert(L2.start == 0 && L2.ptr == 0 && L2.N == 0);
}
void Test_CopyList_ToEmpty() {
    List L1, L2;
    InitList(&L1);
    PutList(&L1, 5);
    PutList(&L1, 7);
    PutList(&L1, 4);
    InitList(&L2);
    CopyList(&L1, &L2);
    assert(L2.N == 3);
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < L1.N; i++) {
        BaseType cont1, cont2;
        ReadList(&L1, &cont1);
        ReadList(&L2, &cont2);
        assert(cont1 == cont2);
        MovePtr(&L1);
        MovePtr(&L2);
    }
    assert(L2.ptr == 0);
}
void Test_CopyList_ToFull() {
    InitMem();
    List L1, L2;
    InitList(&L1);
    PutList(&L1, 5);
    PutList(&L1, 7);
    PutList(&L1, 4);
    InitList(&L2);
    PutList(&L2, 2);
    PutList(&L2, -6);
    PutList(&L2, 1);
    PutList(&L2, 8);
    CopyList(&L1, &L2);
    assert(L2.N == 3);
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < L1.N; i++) {
        BaseType cont1, cont2;
        ReadList(&L1, &cont1);
        ReadList(&L2, &cont2);
        assert(cont1 == cont2);
        MovePtr(&L1);
        MovePtr(&L2);
    }
    assert(L2.ptr == 0);
}

void Test_CopyList() {
    Test_CopyList_Empty();
    Test_CopyList_ToEmpty();
    Test_CopyList_ToFull();
}

void Test_IsProgression_OneElement() {
    List P;
    InitList(&P);
    PutList(&P, 6);
    assert(IsProgression(&P, 1));
}
void Test_IsProgression_SomeElementsRow() {
    List P;
    InitList(&P);
    PutList(&P, 6);
    PutList(&P, 9);
    PutList(&P, 12);
    PutList(&P, 15);
    assert(IsProgression(&P, 3));
}
void Test_IsProgression_SomeElementsNotRow() {
    List P;
    InitList(&P);
    PutList(&P, 6);
    PutList(&P, 9);
    PutList(&P, 11);
    PutList(&P, 14);
    assert(!IsProgression(&P, 3));
}
void Test_IsProgression() {
    Test_IsProgression_OneElement();
    Test_IsProgression_SomeElementsRow();
    Test_IsProgression_SomeElementsNotRow();
}

void List_Test() {
    Test_InitList();
    Test_PutList();
    Test_GetList();
    Test_ReadList();
    Test_FullList();
    Test_EndList();
    Test_Count();
    Test_BeginPtr();
    Test_EndPtr();
    Test_MovePtr();
    Test_MoveTo();
    Test_CopyList();
    /*...*/
    Test_IsProgression();
}

int main() {
    InitMem();
    List_Test();
    printf("All is OK!");
}