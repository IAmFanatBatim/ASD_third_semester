#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../stack/stack.c"
#include "../fifo/fifo.c"

typedef struct {
    char Name[10]; // имя запроса
    unsigned Time; // время обслуживания
    char P; /* приоритет задачи: 0 — высший, 1 — средний, 2 — низший */
} TInquiry;

typedef struct {
    TInquiry *cur_task;
    bool has_task;
    unsigned tasks_before;
} Generator;

typedef struct {
    TInquiry *cur_task;
    bool has_task;
    char delayedP;
} Processor;

bool shouldGenerateTask() {
    return rand() % 100 < 40;
}

void generateTInquiry(TInquiry *T, unsigned tasks_before) {
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int name_len = 2 + rand() % 5;
    for (int i = 0; i < name_len; i++) {
        T->Name[i] = alphabet[rand()%26];
    }
    snprintf(T->Name + name_len, 3, "%d", tasks_before);
    T->Time = 1 + rand()%9;
    T->P = rand()%3;
}

/*void generateTInquiry(TInquiry *T) {
    int name_len = 9;
    for (int i = 0; i < name_len; i++) {
        T->Name[i] = 'q';
    }
    T->Name[name_len] = '\0';
    printf("%s\n", T->Name);
    T->Time = 10;
    T->P = 1;
}*/

void transferTaskToFifo(Generator *G, Fifo *F1, Fifo *F2, Fifo *F3) {
    if (G->has_task) {
        if (G->cur_task->P == 0) {
            PutFifo(F1, G->cur_task);
            printf("F1\n");
        } else if (G->cur_task->P == 1) {
            PutFifo(F2, G->cur_task);
            printf("F2\n");
        } else {
            PutFifo(F3, G->cur_task);
            printf("F3\n");

        }
        G->has_task = 0;
    }
}

char findHighestPriority(Fifo *F1, Fifo *F2, Fifo *F3) {
    if (!EmptyFifo(F1)) {
        return 0;
    } else if (!EmptyFifo(F2)) {
        return 1;
    } else if (!EmptyFifo(F3)) {
        return 2;
    } else {
        return 3;
    }
}

void transferTaskToProcessor(Processor *P, Fifo *F1, Fifo *F2, Fifo *F3) {
    char priority = findHighestPriority(F1, F2, F3);
    if (priority == 0) {
        GetFifo(F1, P->cur_task);
    } else if (priority == 1) {
        GetFifo(F2, P->cur_task);
    } else if (priority == 2) {
        GetFifo(F3, P->cur_task);
    }
}

void shiftOnHigherPriority(Processor *P, Stack *S, Fifo *F1, Fifo *F2, Fifo *F3) {
    char priority = findHighestPriority(F1, F2, F3);
    P->delayedP = P->cur_task->P;
    PutStack(S, P->cur_task);
    transferTaskToProcessor(P, F1, F2, F3);
}

bool shouldReturnToDelayed(Processor *P, Stack *S, Fifo *F1, Fifo *F2) {
    TInquiry *extracted;
    ReadStack(*S, extracted);
    if (extracted->P == P->delayedP) {

    }
}

void returnToDelayed(Processor *P, Stack *S) {
    TInquiry *extracted;
    GetStack(S, extracted);
    P->cur_task = extracted;
}

void makeTact(Generator *G, Processor *P, Stack *S, Fifo *F1, Fifo *F2, Fifo *F3) {
    if (shouldGenerateTask() && G->has_task == 0) {
        printf("!\n");
        generateTInquiry(G->cur_task, G->tasks_before);
        G->has_task = 1;
        printf("Task generated: %s, %d, %d\n", G->cur_task->Name, G->cur_task->Time, G->cur_task->P);
        G->tasks_before += 1;
        transferTaskToFifo(G, F1, F2, F3);
        printf("Task transferred to some Fifo\n");

    }

    if (P->has_task == 0) {
        if (!EmptyStack(*S)) {
            printf("Stack not empty\n");
            if (P->delayedP <= findHighestPriority(F1, F2, F3)) {
                GetStack(S, P->cur_task);
                P->has_task = 1;
                printf("Task transferred: %s, %d, %d\n", P->cur_task->Name, P->cur_task->Time, P->cur_task->P);
            } else {
                printf("Task in stack not prioritized, need to fill processor from Fifo\n");
                printf("%d\n", findHighestPriority(F1, F2, F3));
                transferTaskToProcessor(P, F1, F2, F3);
                P->has_task = 1;
                printf("Task transferred: %s, %d, %d\n", P->cur_task->Name, P->cur_task->Time, P->cur_task->P);
            }
        } else {
            printf("Stack empty, need to fill processor from Fifo\n");
            printf("%d\n", findHighestPriority(F1, F2, F3));
            if (findHighestPriority(F1, F2, F3) != 3) {
                transferTaskToProcessor(P, F1, F2, F3);
                P->has_task = 1;
                printf("Task transferred: %s, %d, %d\n", P->cur_task->Name, P->cur_task->Time, P->cur_task->P);
            } else {
                printf("Fifos empty, no need to fill processor\n");
            }

        }
    } else if (findHighestPriority(F1, F2, F3) < P->cur_task->P) {
        printf("Found more prioritised task\n");
        shiftOnHigherPriority(P, S, F1, F2, F3);
        printf("Task transferred to stack: ");
        TInquiry *last_delayed_task = malloc(sizeof(TInquiry));
        //TInquiry *last_delayed_task;
        ReadStack(*S, (void *)last_delayed_task);
        printf("%s, %d, %d\n", last_delayed_task->Name, last_delayed_task->Time, last_delayed_task->P);
    }
    if (P->has_task) {
        P->cur_task->Time -= 1;
        if (P->cur_task->Time == 0) {
            P->has_task = 0;
        }
    }
}

int main() {
    Generator G;
    Processor P;
    Fifo F1, F2, F3;
    Stack S;
    InitFifo(&F1, sizeof(TInquiry), 50);
    InitFifo(&F2, sizeof(TInquiry), 50);
    InitFifo(&F3, sizeof(TInquiry), 50);
    InitStack(&S, sizeof(TInquiry));
    G.has_task = 0;
    G.tasks_before = 0;
    P.has_task = 0;
    P.delayedP = 2;

    for (int time = 0; time < 20; time++) {
        printf("\nTIME: %d\n", time);
        makeTact(&G, &P, &S, &F1, &F2, &F3);
    }
}
