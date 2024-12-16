#include "stack.c"
#include <assert.h>
#include <stdio.h>


void Test_InitStack() {
    Stack S;
    InitStack(&S, sizeof(int));
    assert(S.ptr == 1 && S.N == 0 && S.Size == sizeof(int));
    DoneStack(&S);
}

void Test_PutStack_ToEmpty() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    PutStack(&S, &a);
    assert(memcmp(&a, S.MemList[0], sizeof(int)) == 0 && S.ptr == 1 && S.N == 1);
    DoneStack(&S);
}
void Test_PutStack_ToNotEmpty() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    int b = 5;
    PutStack(&S, &a);
    PutStack(&S, &b);
    assert(memcmp(&a, S.MemList[1], sizeof(int)) == 0);
    assert(memcmp(&b, S.MemList[0], sizeof(int)) == 0 && S.ptr == 1 && S.N == 2);
    DoneStack(&S);
}
void Test_PutStack() {
    Test_PutStack_ToEmpty();
    Test_PutStack_ToNotEmpty();
}

void Test_GetStack_One() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    PutStack(&S, &a);
    int dest_a;
    GetStack(&S, &dest_a);
    assert(dest_a == 3 && S.ptr == 1 && S.N == 0);
    DoneStack(&S);
}
void Test_GetStack_NotOne() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    int b = 5;
    PutStack(&S, &a);
    PutStack(&S, &b);
    int dest_b, dest_a;
    GetStack(&S, &dest_b);
    GetStack(&S, &dest_a);
    assert(dest_b == 5);
    assert(dest_a == 3 && S.ptr == 1 && S.N == 0);
    DoneStack(&S);
}
void Test_GetStack() {
    Test_GetStack_One();
    Test_GetStack_NotOne();
}

void Test_EmptyStack_Empty() {
    Stack S;
    InitStack(&S, sizeof(int));
    assert(EmptyStack(S));
    DoneStack(&S);
}
void Test_EmptyStack_One() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    PutStack(&S, &a);
    assert(!EmptyStack(S));
    DoneStack(&S);
}
void Test_EmptyStack_NotOne() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    int b = 5;
    PutStack(&S, &a);
    PutStack(&S, &b);
    assert(!EmptyStack(S));
    DoneStack(&S);
}
void Test_EmptyStack() {
    Test_EmptyStack_Empty();
    Test_EmptyStack_One();
    Test_EmptyStack_NotOne();
}

void Test_ReadStack_One() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    PutStack(&S, &a);
    int dest_a;
    ReadStack(S, &dest_a);
    assert(dest_a == 3 && S.ptr == 1 && S.N == 1);
    DoneStack(&S);
}
void Test_ReadStack_NotOne() {
    Stack S;
    InitStack(&S, sizeof(int));
    int a = 3;
    int b = 5;
    PutStack(&S, &a);
    PutStack(&S, &b);
    int dest_b, dest_b2;
    ReadStack(S, &dest_b);
    ReadStack(S, &dest_b2);
    assert(dest_b == 5);
    assert(dest_b2 == 5 && S.ptr == 1 && S.N == 2);
    DoneStack(&S);
}
void Test_ReadStack() {
    Test_ReadStack_One();
    Test_ReadStack_NotOne();
}

void Test_Stack () {
    Test_InitStack();
    Test_PutStack();
    Test_GetStack();
    Test_EmptyStack();
    Test_ReadStack();
}

int main() {
    Test_Stack();
    printf("All is OK!");
}