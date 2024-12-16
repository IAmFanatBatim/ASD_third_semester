#include "tree.h"
#include "tree.c"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>

void Test_InitTree() {
    Tree T;
    InitTree(&T);
    assert(T != NULL);
}

void Test_CreateRoot() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    assert(T != NULL && *T != NULL);
    assert((*T)->LSon == NULL && (*T)->RSon == NULL);
}

void Test_WriteDataTree() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    WriteDataTree(&T, 5);
    assert(T != NULL && *T != NULL);
    assert((*T)->data == 5 && (*T)->LSon == NULL && (*T)->RSon == NULL);
}

void Test_ReadDataTree() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    WriteDataTree(&T, 5);
    BaseType value;
    ReadDataTree(&T, &value);
    assert(T != NULL && *T != NULL);
    assert((*T)->data == 5 && (*T)->LSon == NULL && (*T)->RSon == NULL);
    assert(value == 5);
}

void Test_IsLSon_IsNot() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    assert(!IsLSon(&T));
}

void Test_IsRSon_IsNot() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    assert(!IsRSon(&T));
}

void Test_MoveToLSon_Empty() {
    Tree T, TL;
    InitTree(&T);
    InitTree(&TL);
    CreateRoot(&T);
    MoveToLSon(&T, &TL);
    assert(T != NULL && *T != NULL);
    assert((*T)->LSon == NULL && *TL == NULL);
}

void Test_MoveToRSon_Empty() {
    Tree T, TR;
    InitTree(&T);
    InitTree(&TR);
    CreateRoot(&T);
    MoveToRSon(&T, &TR);
    assert(T != NULL && *T != NULL);
    assert((*T)->RSon == NULL && *TR == NULL);
}

void Test_IsLSon_Is() {
    Tree T, TL;
    InitTree(&T);
    InitTree(&TL);
    CreateRoot(&T);
    MoveToLSon(&T, &TL);
    assert(!IsLSon(&T));
    CreateRoot(&TL);
    assert(IsLSon(&T));
}

void Test_IsRSon_Is() {
    Tree T, TR;
    InitTree(&T);
    InitTree(&TR);
    CreateRoot(&T);
    MoveToRSon(&T, &TR);
    CreateRoot(&TR);
    assert(IsRSon(&T));
}

void Test_IsEmptyTree_IsEmpty() {
    Tree T;
    InitTree(&T);
    assert(IsEmptyTree(&T));
}

void Test_IsEmptyTree_IsNotEmpty() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    assert(!IsEmptyTree(&T));
}

void Test_DelTree_Root() {
    Tree T;
    InitTree(&T);
    CreateRoot(&T);
    DelTree(&T);
    assert(IsEmptyTree(&T));
}

void Test_DelTree_Subtree() {
    Tree T, TR, TRR;
    InitTree(&T);
    InitTree(&TR);
    InitTree(&TRR);
    CreateRoot(&T);
    MoveToRSon(&T, &TR);
    CreateRoot(&TR);
    MoveToRSon(&TR, &TRR);
    CreateRoot(&TRR);
    DelTree(&TR);
    assert(!IsEmptyTree(&T) && !IsRSon(&T));
    assert(IsEmptyTree(&TR));
    assert(!IsEmptyTree(&TRR));
}

void Test_Tree() {
    Test_InitTree();
    Test_CreateRoot();
    Test_WriteDataTree();
    Test_ReadDataTree();
    Test_IsLSon_IsNot();
    Test_IsRSon_IsNot();
    Test_MoveToLSon_Empty();
    Test_MoveToRSon_Empty();
    Test_IsLSon_Is();
    Test_IsRSon_Is();
    Test_IsEmptyTree_IsEmpty();
    Test_IsEmptyTree_IsNotEmpty();
    Test_DelTree_Root();
    Test_DelTree_Subtree();
}

int main() {
    Test_Tree();
    printf("All is OK!");
    return 0;
}
