#include "fifo.c"
#include <assert.h>
#include <stdio.h>


void Test_InitFifo() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    assert(F.SizeEl == sizeof(int) && F.SizeBuf == 5 && F.N == 0 && F.Uk1 == 0 && F.Uk2 == 0);
    DoneFifo(&F);
}

void Test_PutFifo_ToEmpty() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    PutFifo(&F, &a);
    assert(memcmp(&a, F.Buf[0], sizeof(int)) == 0 && F.Uk2 == 1 && F.N == 1);
    DoneFifo(&F);
}
void Test_PutFifo_ToNotEmpty() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    int b = 5;
    PutFifo(&F, &a);
    PutFifo(&F, &b);
    assert(memcmp(&a, F.Buf[0], sizeof(int)) == 0);
    assert(memcmp(&b, F.Buf[1], sizeof(int)) == 0 && F.Uk2 == 2 && F.N == 2);
    DoneFifo(&F);
}
void Test_PutFifo() {
    Test_PutFifo_ToEmpty();
    Test_PutFifo_ToNotEmpty();
}

void Test_GetFifo_One() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    PutFifo(&F, &a);
    int dest_a;
    GetFifo(&F, &dest_a);
    assert(dest_a == 3 && F.Uk1 == 1 && F.N == 0);
    DoneFifo(&F);
}
void Test_GetFifo_NotOne() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    int b = 5;
    PutFifo(&F, &a);
    PutFifo(&F, &b);
    int dest_a, dest_b;
    GetFifo(&F, &dest_a);
    GetFifo(&F, &dest_b);
    assert(dest_b == 5);
    assert(dest_a == 3 && F.Uk1 == 2 && F.N == 0);
    DoneFifo(&F);
}
void Test_GetFifo() {
    Test_GetFifo_One();
    Test_GetFifo_NotOne();
}

void Test_EmptyFifo_Empty() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    assert(EmptyFifo(&F));
    DoneFifo(&F);
}
void Test_EmptyFifo_One() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    PutFifo(&F, &a);
    assert(!EmptyFifo(&F));
    DoneFifo(&F);
}
void Test_EmptyFifo_NotOne() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    int b = 5;
    PutFifo(&F, &a);
    PutFifo(&F, &b);
    assert(!EmptyFifo(&F));
    DoneFifo(&F);
}
void Test_EmptyFifo() {
    Test_EmptyFifo_Empty();
    Test_EmptyFifo_One();
    Test_EmptyFifo_NotOne();
}

void Test_ReadFifo_One() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    PutFifo(&F, &a);
    int dest_a;
    ReadFifo(&F, &dest_a);
    assert(dest_a == 3 && F.Uk1 == 0 && F.N == 1);
    DoneFifo(&F);
}
void Test_ReadFifo_NotOne() {
    Fifo F;
    InitFifo(&F, sizeof(int), 5);
    int a = 3;
    int b = 5;
    PutFifo(&F, &a);
    PutFifo(&F, &b);
    int dest_a, dest_a2;
    ReadFifo(&F, &dest_a);
    ReadFifo(&F, &dest_a2);
    assert(dest_a == 3);
    assert(dest_a2 == 3 && F.Uk1 == 0 && F.N == 2);
    DoneFifo(&F);
}
void Test_ReadFifo() {
    Test_ReadFifo_One();
    Test_ReadFifo_NotOne();
}


void Test_Fifo () {
    Test_InitFifo();
    Test_PutFifo();
    Test_GetFifo();
    Test_EmptyFifo();
    Test_ReadFifo();
}

int main() {
    Test_Fifo();
    printf("All is OK!");
}