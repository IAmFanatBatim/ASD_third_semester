#include <stdio.h>

typedef int BaseType;

typedef unsigned ptrel;

typedef struct {
    BaseType data;
    ptrel next;
} element;

typedef struct {
    ptrel start;
    ptrel ptr;
    unsigned int N;
} List;

void PrintList(List *L, element *cont) {
    L->ptr = L->start;
    for (int i = 0; i < L->N; i++) {
        printf("%d, ", cont[L->ptr].data);
        L->ptr = cont[L->ptr].next;
    }
    printf("\b\b \n");
}

int main() {
    element ListsContainer[10] = {
            {0, 2},
            {1, 3},
            {0, 6},
            {5, 5},
            {-7, 0},
            {6, 4},
            {0, 9},
            {2, 0},
            {3, 7},
            {0, 0}
    };
    List L1, L2;
    L1 = (List) {1, 1, 4};
    L2 = (List) {8, 8, 2};
    PrintList(&L1, ListsContainer);
    PrintList(&L2, ListsContainer);
}