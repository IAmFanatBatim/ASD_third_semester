#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Обменивает значениями переменные типа int по адресам a и b
void swapInt(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Возвращает максимальное из значений переменных a и b
int max2(int a, int b) {
    return (a > b) ? a : b;
}

//Возвращает логарифм числа argument по основанию base, округленный вверх, если is_ceil = 1, и округленный вниз в противном случае
int logarithm(size_t argument, int base, bool is_ceil) {
    int cur_argument = 1;
    int logarithm = 0;
    while (cur_argument < argument) {
        cur_argument *= base;
        logarithm++;
    }
    if (!is_ceil) {
        return (cur_argument == argument) ? logarithm : logarithm - 1;
    } else {
        return logarithm;
    }
}

//Осуществляет сортировку включением (вставками) массива array размера size
void insertSort(int *array, int size) {
    for (int cur_ind = 1; cur_ind < size; cur_ind++) {
        int cur_el = array[cur_ind];
        int insert_ind = cur_ind;
        while (array[insert_ind - 1] > cur_el && insert_ind > 0) {
            array[insert_ind] = array[insert_ind - 1];
            insert_ind--;
        }
        array[insert_ind] = cur_el;
    }
}

//Осуществляет сортировку выбором массива array размера size
void choiceSort(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        int cur_min_ind = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j] < array[cur_min_ind]) {
                cur_min_ind = j;
            }
        }
        swapInt(array + i, array + cur_min_ind);
    }
}

//Осуществляет сортировку обменом (пузырьковую сортировку) массива array размера size
void bubbleSort(int *array, int size) {
    for (int n = 0; n < size - 1; n++) {
        for (int i = size - 1; i > n; i--) {
            if (array[i] < array[i-1]) {
                swapInt(array + i, array + i - 1 );
            }
        }
    }
}

//Осуществляет сортировку обменом (пузырьковую сортировку) с проверкой на наличие перестановок в текущем внешнем цикле массива array размера size
void bubbleSort_improve1(int *array, int size) {
    for (int n = 0; n < size - 1; n++) {
        bool are_exchange = false;
        for (int i = size - 1; i > n; i--) {
            if (array[i] < array[i-1]) {
                swapInt(array + i, array + i - 1 );
                are_exchange = true;
            }
        }
        if (!are_exchange) {
            break;
        }
    }
}

//Осуществляет сортировку обменом (пузырьковую сортировку) с учетом индекса последней перестановки в прошлом внешнем цикле массива array размера size
void bubbleSort_improve2 (int *array, int size) {
    int exchange_ind = 0;
    int cur_exchange_ind = size-1;
    for (int n = 0; n < size - 1; n++) {
        for (int i = size - 1; i > exchange_ind; i--) {
            if (array[i] < array[i-1]) {
                swapInt(array + i, array + i - 1);
                cur_exchange_ind = i;
            }
        }
        exchange_ind = cur_exchange_ind;
    }
}

void shellSort (int *array, int size) {
    int amount_of_repeats = logarithm(size, 3, 0) - 1;
    if (amount_of_repeats < 1) {
        amount_of_repeats = 1;
    }
    int h = 1;
    for (int i = 1; i < amount_of_repeats; i++) {
        h = 3*h + 1;
    }
    //printf("%d %d \n",amount_of_repeats, h);
    while (h > 0) {
        for (int cur_ind = h; cur_ind < size; cur_ind++) {
            int cur_el = array[cur_ind];
            int insert_ind = cur_ind;
            while (array[insert_ind - h] > cur_el && insert_ind > 0) {
                array[insert_ind] = array[insert_ind - h];
                insert_ind -= h;
            }
            array[insert_ind] = cur_el;
        }
        h = (h-1) / 3;
    }
}

//Осуществляет сортировку Хоара (быструю сортировку) массива array размера size
void quickSort(int *array, int size) {
    int reference_ind = 0;
    int left_ind = 0;
    int right_ind = size - 1;
    while (left_ind <= right_ind) {
        while (array[left_ind] < array[reference_ind] && left_ind < size) {
            left_ind++;
        }
        while (array[right_ind] > array[reference_ind] && right_ind >= 0) {
            right_ind--;
        }
        if (left_ind <= right_ind) {
            swapInt(array + left_ind, array + right_ind);
            left_ind++;
            right_ind--;
        }
    }
    if (right_ind > 0) {
        quickSort(array, right_ind + 1);
    }
    if (left_ind < size - 1) {
        quickSort(array + left_ind, size - left_ind);
    }
}

//Преобразует массив array размера size, который в виде бинарного дерева не является пирамидой, но имеет ветви, являющиеся пирамидами, в пирамиду
void makeHeap(int *array, int first_ind, int last_ind) {
    int root_el, cur_son_ind, cur_parent_ind;
    root_el = array[first_ind];
    cur_son_ind = 2*first_ind+1;
    cur_parent_ind = first_ind;
    if ((cur_son_ind<last_ind) && (array[cur_son_ind]<array[cur_son_ind+1])) {
        cur_son_ind++;
    }
    while ((cur_son_ind<=last_ind) && (root_el<array[cur_son_ind])) {
        swapInt(&array[cur_son_ind], &array[cur_parent_ind]);
        cur_parent_ind = cur_son_ind;
        cur_son_ind = 2*cur_son_ind+1;
        if ((cur_son_ind<last_ind) && (array[cur_son_ind]<array[cur_son_ind+1])) {
            cur_son_ind++;
        }
    }
}

//Осуществляет пирамидальную сортировку массива array размера size
void heapSort(int *array, int size) {
    int first_ind, last_ind;
    first_ind = size/2 ; last_ind = size-1;
    while (first_ind > 0) {
        first_ind = first_ind - 1;
        makeHeap(array, first_ind, last_ind);
    }
    while (last_ind > 0) {
        swapInt(&array[0], &array[last_ind]);
        last_ind--;
        makeHeap(array, first_ind, last_ind);
    }
}