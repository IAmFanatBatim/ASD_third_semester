#ifndef __STACK_5_C
#define __STACK_5_C
#include "Stack_5.h"
#include "../АСД 5 си/list.c"

void InitStack(Stack *s) {
    InitList(s);
}

void PutStack(Stack *s, BaseType E) {
    PutList(s, E);
    s->ptr = 0;
}

void GetStack(Stack *s, BaseType *E) {
    s->ptr = s->start;
    GetList(s, E);
    s->ptr = 0;
}

int EmptyStack(Stack *s) {
    return !FullList(s);
}

void ReadStack(Stack *s, BaseType *E) {
    ReadList(s, E);
}

void DoneStack(Stack *s) {
    DoneList(s);
}

#endif
