#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../stack/stack.c"
#include "../fifo/fifo.c"

typedef struct {
    char Name[10]; //имя запроса
    unsigned Time; //время обслуживания
    char P;        //приоритет задачи: 0 — высший, 1 — средний, 2 — низший
} TInquiry;

typedef struct {
    TInquiry *cur_task;     //указатель на содержащуюся в нем задачу
    bool has_task;          //флаг: находится ли задача по указателю
    unsigned tasks_before;  //количество уже сгенерированных задач
} Generator;

typedef struct {
    TInquiry *cur_task; //указатель на содержащуюся в нем задачу
    bool has_task;      //флаг: находится ли задача по указателю
    char delayedP;      //Приоритет отложенной задачи; если отложенной задачи нет, равен 3
} Processor;

//Возвращает значение "истина" с вероятностью 60 процентов
bool shouldGenerateTask() {
    return rand() % 100 < 60;
}

//Задает приоритет со следующим распределением: 30% - приоритет 0, 30% - приоритет 1, 40% - приоритет 2
int generatePriority() {
    int num = rand() % 100;
    if (num < 30) {
        return 0;
    } else if (num < 60) {
        return 1;
    } else {
        return 2;
    }
}

//Записывает по адресу cur_task генератора задач G задачу с:
// 1) именем из случайных символов (их количество может варьироваться от 2 до 7) и порядкового кномера задачи,
// 2) случайным временем выполнения (варьируется от 2 до 7 тактов),
// 3) случайным приоритетом, определяемым значением функции generatePriority
//После этого к счетчику сгенерированных задач прибавляется 1, а флаг, обозначающий, находится ли в массиве задача, принимает значение "истина"
void generateTInquiry(Generator *G) {
    char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    int name_len = 2 + rand() % 6;
    for (int i = 0; i < name_len; i++) {
        G->cur_task->Name[i] = alphabet[rand()%26];
    }
    snprintf(G->cur_task->Name + name_len, 3, "%d", G->tasks_before);
    G->cur_task->Time = 2 + rand()%6;
    G->cur_task->P = generatePriority();
    G->has_task = true;
    G->tasks_before += 1;
}

//Если генератор задач G содержит задачу, переносит ее в одлну из очередей F1, F2, F3 в зависимости от ее приоритета
//После этого флаг, обозначающий, находится ли в массиве задача, принимает значение "ложь"
void transferTaskToFifo(Generator *G, Fifo *F1, Fifo *F2, Fifo *F3) {
    if (G->has_task) {
        if (G->cur_task->P == 0) {
            PutFifo(F1, G->cur_task);
        } else if (G->cur_task->P == 1) {
            PutFifo(F2, G->cur_task);
        } else {
            PutFifo(F3, G->cur_task);
        }
        G->has_task = 0;
    }
}

//Возвращает наивысший приоритет среди содержащихся в очереди задач
//Приоритеты 0, 1, 2 соотвествуют очередям F1, F2, F3 соответственно. Если все эти очереди пусты, возвращается 3
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

//Переносит из непустой очереди с наивысшим приоритетом (среди очередей F1, F2, F3) задачу в процессор P, устанавливает флаг наличия задачи в процессоре в "истина"
//Если непустая очередь не найдена, переноса не происходит
void transferTaskToProcessor(Processor *P, Fifo *F1, Fifo *F2, Fifo *F3) {
    char priority = findHighestPriority(F1, F2, F3);
    if (priority == 0) {
        GetFifo(F1, P->cur_task);
        P->has_task = 1;
    } else if (priority == 1) {
        GetFifo(F2, P->cur_task);
        P->has_task = 1;
    } else if (priority == 2) {
        GetFifo(F3, P->cur_task);
        P->has_task = 1;
    }
}

//Выполняет перенос задачи из процессора P в стек S, после чего заполняет процессор новой задачей из очереди с наивысшим приоритетом
void shiftOnHigherPriority(Processor *P, Stack *S, Fifo *F1, Fifo *F2, Fifo *F3) {
    P->delayedP = P->cur_task->P;
    PutStack(S, P->cur_task);
    transferTaskToProcessor(P, F1, F2, F3);
}

//Считывает последнюю задачу в стеке отложенных задач S и на ее основании обновляет параметр delayedP в процессорве P
void updateDelayedP(Processor *P, Stack *S) {
    if (!EmptyStack(*S)) {
        TInquiry last_delayed;
        ReadStack(*S, &last_delayed);
        P->delayedP = last_delayed.P;
    } else {
        P->delayedP = 3;
    }
}

//Выводит на экран задачу T в формате (имя;время;приоритет)
void outputTInquiry(TInquiry *T) {
    printf("(%s;%d)", T->Name, T->Time);
}

//Выводит на экран задачу, содержащуюся в процессоре P; если процессор не содержит задачу, выводится сообщение "empty"
void outputProcessor (Processor *P) {
    if (P->has_task == 0) {
        printf("empty");
    } else {
        outputTInquiry(P->cur_task);
    }
}

//Выводит на экран задачи, содержащиеся в очереди F; если очередь не содержит задач, выводится сообщение "empty"
void outputFifo (Fifo *F) {
    if (EmptyFifo(F)) {
        printf("empty");
    } else {
        Fifo tempFifo;
        InitFifo(&tempFifo, F->SizeEl, F->SizeBuf);
        TInquiry *task = malloc(sizeof(TInquiry));
        while (!EmptyFifo(F)) {
            GetFifo(F, task);
            outputTInquiry(task);
            printf(",");
            PutFifo(&tempFifo, task);
        }
        printf("\b ");
        while (!EmptyFifo(&tempFifo)) {
            GetFifo(&tempFifo, task);
            PutFifo(F, task);
        }
        DoneFifo(&tempFifo);
    }
}

//Выводит на экран задачи, содержащиеся в стеке S; если стек не содержит задач, выводится сообщение "empty"
void outputStack (Stack *S) {
    if (EmptyStack(*S)) {
        printf("empty");
    } else {
        Stack tempStack;
        InitStack(&tempStack, S->Size);
        TInquiry *task = malloc(sizeof(TInquiry));
        while (!EmptyStack(*S)) {
            GetStack(S, task);
            outputTInquiry(task);
            printf(",");
            PutStack(&tempStack, task);
        }
        printf("\b ");
        while (!EmptyStack(tempStack)) {
            GetStack(&tempStack, task);
            PutStack(S, task);
        }
        DoneStack(&tempStack);
    }
}

//Моделирует выполнение одного такта системы из генератора задач G, процессора P, стека S и очередей F1, F2, F3
//Выводит состояние всех компонентов системы, кроме генератора задач, по завершению такта
void makeTact(Generator *G, Processor *P, Stack *S, Fifo *F1, Fifo *F2, Fifo *F3) {
    if (shouldGenerateTask() && G->has_task == 0) {
        generateTInquiry(G);
    }
    transferTaskToFifo(G, F1, F2, F3);
    if (P->has_task == 0) {
        if (!EmptyStack(*S) && P->delayedP <= findHighestPriority(F1, F2, F3)) {
            GetStack(S, P->cur_task);
            P->has_task = 1;
            updateDelayedP(P, S);
        } else {
            transferTaskToProcessor(P, F1, F2, F3);
        }
    } else if (findHighestPriority(F1, F2, F3) < P->cur_task->P) {
        shiftOnHigherPriority(P, S, F1, F2, F3);
    }
    if (P->has_task) {
        P->cur_task->Time -= 1;
        if (P->cur_task->Time == 0) {
            P->has_task = 0;
        }
    }
    printf("Fifo No1: ");
    outputFifo(F1);
    printf("\nFifo No2: ");
    outputFifo(F2);
    printf("\nFifo No3: ");
    outputFifo(F3);
    printf("\nStack: ");
    outputStack(S);
    printf("\nProcessor: ");
    outputProcessor(P);
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
    P.delayedP = 3;

    for (int time = 1; time <= 20; time++) {
        printf("\n\nTIME: %d\n", time);
        makeTact(&G, &P, &S, &F1, &F2, &F3);
    }
}
