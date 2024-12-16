#include "SLList.c"
#include <assert.h>
#include <stdio.h>


void Test_InitList() {
    List L;
    InitList(&L, 10);
    assert(L.ptr == 0 && L.N == 0 && L.Size == 10);
}

void Test_PutList_InEmpty() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    assert(L.MemList[0] == 5 && L.ptr == 1 && L.N == 1);
}
void Test_PutList_AtEnd() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    assert(L.MemList[0] == 5 && L.MemList[1] == 7 && L.ptr == 2 && L.N == 2);
}
void Test_PutList_AtBeginning() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    L.ptr = 0;
    PutList(&L, 7);
    assert(L.MemList[0] == 7 && L.MemList[1] == 5 && L.ptr == 1 && L.N == 2);
}
void Test_PutList_Between() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_at_first = L.ptr;
    PutList(&L, 7);
    L.ptr = ptr_at_first;
    PutList(&L, 4);
    assert(L.MemList[0] == 5 && L.MemList[1] == 4 && L.MemList[2] == 7 && L.ptr == 2 && L.N == 3);
}
void Test_PutList() {
    Test_PutList_InEmpty();
    Test_PutList_AtEnd();
    Test_PutList_AtBeginning();
    Test_PutList_Between();
}

void Test_GetList_OneAndOnly() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    BaseType container;
    GetList(&L, &container);
    assert(container == 5 && L.ptr == 0 && L.N == 0);
}
void Test_GetList_AtEnd() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    BaseType container;
    GetList(&L, &container);
    assert(container == 7 && L.MemList[0] == 5 && L.ptr == 1 && L.N == 1);
}
void Test_GetList_AtBeginning() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_at_first = L.ptr;
    PutList(&L, 7);
    L.ptr = ptr_at_first;
    BaseType container;
    GetList(&L, &container);
    assert(container == 5 && L.MemList[0] == 7 && L.N == 1);
}
void Test_GetList_Between() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_at_second = L.ptr;
    PutList(&L, 4);
    L.ptr = ptr_at_second;
    BaseType container;
    GetList(&L, &container);
    assert(container == 7 && L.MemList[0] == 5 && L.MemList[1] == 4 && L.N == 2);
}
void Test_GetList() {
    Test_GetList_OneAndOnly();
    Test_GetList_AtEnd();
    Test_GetList_AtBeginning();
    Test_GetList_Between();
}

void Test_ReadList_OneAndOnly() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    BaseType container;
    ReadList(&L, &container);
    assert(container == 5 && L.MemList[0] == 5);
}
void Test_ReadList_AtEnd() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    BaseType container;
    ReadList(&L, &container);
    assert(container == 7 && L.MemList[1] == 7);
}
void Test_ReadList_AtBeginning() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_at_first = L.ptr;
    PutList(&L, 7);
    L.ptr = ptr_at_first;
    BaseType container;
    ReadList(&L, &container);
    assert(container == 5 && L.MemList[0] == 5);
}
void Test_ReadList_Between() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_at_second = L.ptr;
    PutList(&L, 4);
    L.ptr = ptr_at_second;
    BaseType container;
    ReadList(&L, &container);
    assert(container == 7 && L.MemList[1] == 7);
}
void Test_ReadList() {
    Test_ReadList_OneAndOnly();
    Test_ReadList_AtEnd();
    Test_ReadList_AtBeginning();
    Test_ReadList_Between();
}

void Test_FullList_Empty() {
    List L;
    InitList(&L, 10);
    assert(!FullList(&L));
}
void Test_FullList_SomeElementsIn() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    assert(!FullList(&L));
}
void Test_FullList_PtrAt0() {
    List L;
    InitList(&L, 3);
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
    InitList(&L, 10);
    PutList(&L, 5);
    assert(EndList(&L));
}
void Test_EndList_PtrAtEnd() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    assert(EndList(&L));
}
void Test_EndList_PtrInMiddle() {
    List L;
    InitList(&L, 10);
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
    InitList(&L, 10);
    assert(Count(&L) == 0);
}
void Test_Count_OneElement() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    assert(Count(&L) == 1);
}
void Test_Count_SomeElements() {
    List L;
    InitList(&L, 10);
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
    InitList(&L, 10);
    BeginPtr(&L);
    assert(L.ptr == 0);
}
void Test_BeginPtr_OneElement() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_start = L.ptr;

    BeginPtr(&L);
    assert(L.ptr == ptr_start);
}
void Test_BeginPtr_SomeElements() {
    List L;
    InitList(&L, 10);
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
    InitList(&L, 10);
    BeginPtr(&L);
    assert(L.ptr == 0);
}
void Test_EndPtr_OneElement() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_end = L.ptr;
    EndPtr(&L);
    assert(L.ptr == ptr_end);
}
void Test_EndPtr_SomeElements() {
    List L;
    InitList(&L, 10);
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

void Test_MovePtr_SomeElementsFromFirst() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    BeginPtr(&L);
    MovePtr(&L);
    assert(L.ptr == 2);
}
void Test_MovePtr_SomeElementsFromMiddle() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_second = L.ptr;
    PutList(&L, 4);
    ptrel ptr_last = L.ptr;
    L.ptr = ptr_second;
    MovePtr(&L);
    assert(L.ptr == ptr_last);
}

void Test_MovePtr() {
    Test_MovePtr_SomeElementsFromFirst();
    Test_MovePtr_SomeElementsFromMiddle();
}

void Test_MoveTo_OneElement() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_first = L.ptr;
    L.ptr = 0;
    MoveTo(&L, 1);
    assert(L.ptr == ptr_first);
}
void Test_MoveTo_SomeElementsToFirst() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    ptrel ptr_first = L.ptr;
    PutList(&L, 7);
    PutList(&L, 4);
    MoveTo(&L, 1);
    assert(L.ptr == ptr_first);
}
void Test_MoveTo_SomeElementsToMiddle() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    ptrel ptr_second = L.ptr;
    PutList(&L, 4);
    MoveTo(&L, 2);
    assert(L.ptr == ptr_second);
}
void Test_MoveTo_SomeElementsToLast() {
    List L;
    InitList(&L, 10);
    PutList(&L, 5);
    PutList(&L, 7);
    PutList(&L, 4);
    ptrel ptr_last = L.ptr;
    BeginPtr(&L);
    MoveTo(&L, 3);
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
    InitList(&L1, 10);
    InitList(&L2, 10);
    CopyList(&L1, &L2);
    assert(L2.N == 0);
}
void Test_CopyList_ToEmpty() {
    List L1, L2;
    InitList(&L1, 10);
    PutList(&L1, 5);
    PutList(&L1, 7);
    PutList(&L1, 4);
    InitList(&L2, 10);
    CopyList(&L1, &L2);
    assert(L2.N == 3);
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < L2.N; i++) {
        BaseType cont1, cont2;
        ReadList(&L1, &cont1);
        ReadList(&L2, &cont2);
        assert(cont1 == cont2);
        MovePtr(&L1);
        MovePtr(&L2);
    }
}

void Test_CopyList_ToFull() {
    List L1, L2;
    InitList(&L1, 10);
    PutList(&L1, 5);
    PutList(&L1, 7);
    PutList(&L1, 4);
    InitList(&L2, 10);
    PutList(&L2, 2);
    PutList(&L2, -6);
    PutList(&L2, 1);
    PutList(&L2, 8);
    CopyList(&L1, &L2);
    assert(L2.N == 3);
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < L2.N; i++) {
        BaseType cont1, cont2;
        ReadList(&L1, &cont1);
        ReadList(&L2, &cont2);
        assert(cont1 == cont2);
        MovePtr(&L1);
        MovePtr(&L2);
    }
}

void Test_CopyList() {
    Test_CopyList_Empty();
    Test_CopyList_ToEmpty();
    Test_CopyList_ToFull();
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
}

int main() {
    List_Test();
    printf("All is OK!");
}