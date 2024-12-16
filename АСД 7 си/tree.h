#ifndef __TREE1_H
#define __TREE1_H
const short TreeOk = 0;
const short TreeNotMem = 1;
const short	TreeUnder = 2;
short TreeError;

typedef	int BaseType;

typedef struct Element {
    BaseType data;
    struct Element *LSon;
    struct Element *RSon;
} element;
typedef element* PtrEl;
typedef PtrEl *Tree;

//Инициализация — создается элемент, который будет содержать корень дерева
void InitTree(Tree *T);
//Создание корня
void CreateRoot(Tree *T);
//Запись данных
void WriteDataTree(Tree *T, BaseType E);
//Чтение
void ReadDataTree(Tree *T,BaseType *E);
//1 — есть левый сын, 0 — нет
int IsLSon(Tree *T);
//1 — есть правый сын, 0 — нет
int IsRSon(Tree *T);
//Перейти к левому сыну, где T — адрес ячейки, содержащей адрес текущей вершины, TS — адрес ячейки, содержащей адрес корня левого поддерева(левого сына)
void MoveToLSon(Tree *T, Tree *TS);
//Перейти к правому сыну
void MoveToRSon(Tree *T, Tree *TS);
//1 — пустое дерево, 0 — не пустое
int IsEmptyTree(Tree *T);
//Удаление листа
void DelTree(Tree *T);

#endif
