#if !defined(__FIFO11_H)
#define __FIFO11_H
const int FifoOk = 0;
const int FifoUnder = 1;
const int FifoOver = 2;
int FifoError; // Переменная ошибок

typedef void *BaseType;
typedef struct {
    BaseType *Buf;
    unsigned SizeBuf; // Максимальная длина очереди
    unsigned SizeEl; // Размер элемента очереди
    unsigned Uk1; // Указатель на «голову» очереди
    unsigned Uk2; // Указатель на «хвост» очереди
    unsigned N;   // Количество элементов очереди
} Fifo;

// Инициализация очереди по адресу f
void InitFifo(Fifo* f, unsigned SizeEl, unsigned SizeBuf);
//Поместить элемент из переменной по адресу E в очередь по адресу f
void PutFifo(Fifo *f, void *E);
//Извлечь элемент из очереди по адресу f и записать его в переменую по адресу E
void GetFifo(Fifo *f, void *E);
//Прочитать элемент очереди по адресу f и записать его в переменую по адресу E
void ReadFifo(Fifo *f, void *E);
//Проверка, пуста ли очередь по адресу f
int EmptyFifo(Fifo *f);
//Разрушить очередь по адресу f
void DoneFifo(Fifo *f);

#endif
