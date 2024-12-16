#ifndef __STACK10_C
#define __STACK10_C
#include "stack.h"
#include "../SLList/SLList.c"

void InitStack(Stack *s, unsigned Size) {
    InitList(s, Size);
    s->ptr = 1;
}

void PutStack(Stack *s, void *E) {
    s->ptr = 0;
    PutList(s, E);
    s->ptr = 1;
}

void GetStack(Stack *s, void *E) {
    GetList(s, E);
    s->ptr = 1;
}

int EmptyStack(Stack s) {
    return !FullList(&s);
}

void ReadStack(Stack s, void *E) {
    ReadList(&s, E);
    s.ptr = 1;
}

void DoneStack(Stack *s) {
    DoneList(s);
}
		
#endif