#ifndef __TREE1_C
#define __TREE1_C
#include "tree.h"
#include <malloc.h>

void InitTree(Tree *T) {
    *T = malloc(sizeof(PtrEl));
    if (*T == NULL) {
        TreeError = TreeNotMem;
        exit(TreeError);
    } else {
        (**T) = NULL;
        TreeError = TreeOk;
    }
}

void CreateRoot(Tree *T) {
    **T = malloc(sizeof(element));
    if (**T == NULL) {
        TreeError = TreeNotMem;
        exit(TreeError);
    } else {
        (**T)->LSon = NULL;
        (**T)->RSon = NULL;
        TreeError = TreeOk;
    }
}

void WriteDataTree(Tree *T, BaseType E) {
    if (**T == NULL) {
        TreeError = TreeUnder;
        exit(TreeError);
    } else {
        (**T)->data = E;
    }
}

void ReadDataTree(Tree *T, BaseType *E) {
    if (**T == NULL) {
        TreeError = TreeUnder;
        exit(TreeError);
    } else {
        *E = (**T)->data;
    }
}

int IsLSon(Tree *T) {
    return ((**T)->LSon != NULL);
}

int IsRSon(Tree *T) {
    return ((**T)->RSon != NULL);
}

void MoveToLSon(Tree *T, Tree *TS) {
    *TS = &(**T)->LSon;
}

void MoveToRSon(Tree *T, Tree *TS) {
    *TS = &(**T)->RSon;
}

int IsEmptyTree(Tree *T) {
    return (**T) == NULL;
}

void DelTree(Tree *T) {
    (**T) = NULL;
}

#endif
