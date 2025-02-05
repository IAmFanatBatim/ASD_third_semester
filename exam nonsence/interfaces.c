#ifndef STACK_ARRAY
#define STACK_ARRAY
const short StackSize = 100;
const short StackOk = 0;
const short StackEmpty = 1;
const short StackFull = 2;
extern short StackError;

typedef <...> BaseType
typedef struct {
    BaseType Buf[StackSize];
    short Uk;
} Stack;

void InitStack(Stack *s);
void PutStack(Stack *s, BaseType E);
void GetStack(Stack *s, BaseType *E);
void ReadStack(Stack *s, BaseType *E);
void EmptyStack(Stack s);
void FullStack(Stack s);
void DoneStack(Stack *s);
#endif

#ifndef FIFO_ARRAY
#define FIFO_ARRAY
const short FifoSize = 100;
const short FifoOk = 0;
const short FifoEmpty = 1;
const short FifoFull = 2;
short FifoError;

typedef <...> BaseType;
typedef struct {
    BaseType Buf[FifoSize];
    short Uk1;
    short Uk2;
    short N;
} Fifo;

void InitFifo(Fifo* f);
void PutFifo(Fifo *f, BaseType E);
void GetFifo(Fifo *f, BaseType *E);
void ReadFifo(Fifo *f, BaseType *E);
int EmptyFifo(Fifo f);
int FullFifo(Fifo f);
void DoneFifo(Fifo *f);

#endif