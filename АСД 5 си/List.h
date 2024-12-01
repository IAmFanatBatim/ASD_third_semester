#if !defined(__LIST5_H)
#define __LIST5_H

#define SizeList 100

const short ListOk = 0;
const short ListNotMem = 1;
const short ListUnder = 2;
const short ListEnd = 3;
short ListError;

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

element MemList[SizeList];

//Инициализация списка, который создается по адресу L
void InitList(List *L);
//Включение элемента со значением E в список по адресу L
void PutList(List *L, BaseType E);
//Исключение элемента из списка по адресу L и сохранение его в переменной по адресу E
void GetList(List *L, BaseType *E);
//Чтение элемента списка по адресу L и сохранение его в переменной по адресу E
void ReadList(List *L,BaseType *E);
//Возвращает 1, если список по адресу L не пуст, И 0 в противном случае
int FullList(List *L);
// проверка: является ли элемент списка по адресу L последним
int EndList(List *L);
//Возвращает количество элементов в списке по адресу L
unsigned int Count(List *L);
//Установка в начало списка по адресу L
void BeginPtr(List *L);
//Установка в конец списка по адресу L
void EndPtr(List *L);
//Переход к следующему элементу в списке по адресу L
void MovePtr(List *L);
//Переход к n-му элементу в списке по адресу L
void MoveTo(List *L, unsigned int n);
//Удаление списка по адресу L
void DoneList(List *L);
//Копирование списка по адресу L1 в список по адресу L2
void CopyList(List *L1,List *L2);
//Связывает все элементы массива в список свободных элементов
void InitMem();
//Возвращает 1, если в массиве нет свободных элементов, и 0 в противном случае
int EmptyMem();
//Возвращает номер свободного элемента и исключает его из ССЭ
unsigned NewMem();
//делает n-й элемент массива свободным и включает его в ССЭ
void DisposeMem(unsigned n);

int IsProgression (List *P, int h);

#endif