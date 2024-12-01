#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Сохраняет по адресу array массив целых чисел размера size со случайными значениями в диапазоне от size/2 до -size/2
void generateRandomArray(int *array, int size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = rand() % size - size/2;
    }
}

//Сохраняет по адресу array массив целых чисел размера size со значениями в диапазоне от -size/2 до size/2, идущими в порядке возрастания с шагом 1
void generateOrderedArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i - size/2;
    }
}

//Сохраняет по адресу array массив целых чисел размера size со значениями в диапазоне от size/2 до -size/2, идущими в порядке убывания с шагом 1
void generateOrderedBackwards(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = size/2 - i;
    }
}

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

int insertSort(int *array, int size) {
    int compares = 0;
    for (int cur_ind = 1; cur_ind < size; cur_ind++, compares++) {
        int cur_el = array[cur_ind];
        int insert_ind = cur_ind;
        while (array[insert_ind - 1] > cur_el && insert_ind > 0) {
            array[insert_ind] = array[insert_ind - 1];
            insert_ind--;
            compares+=2;
        }
        compares+=2;
        array[insert_ind] = cur_el;
    }
    compares++;
    return compares;
}

int choiceSort(int *array, int size) {
    int compares = 0;
    for (int i = 0; i < size - 1; i++, compares++) {
        int cur_min_ind = i;
        for (int j = i + 1; j < size; j++, compares++) {
            compares++;
            if (array[j] < array[cur_min_ind]) {
                cur_min_ind = j;
            }
        }
        compares++;
        swapInt(array + i, array + cur_min_ind);
    }
    compares++;
    return compares;
}

int bubbleSort(int *array, int size) {
    int compares = 0;
    for (int n = 0; n < size - 1; n++, compares++) {
        for (int i = size - 1; i > n; i--, compares++) {
            compares++;
            if (array[i] < array[i-1]) {
                swapInt(array + i, array + i - 1 );
            }
        }
        compares++;
    }
    compares++;
    return compares;
}

int bubbleSort_improve1(int *array, int size) {
    int compares = 0;
    for (int n = 0; n < size - 1; n++, compares++) {
        bool are_exchange = false;
        for (int i = size - 1; i > n; i--, compares++) {
            compares++;
            if (array[i] < array[i-1]) {
                swapInt(array + i, array + i - 1 );
                are_exchange = true;
            }
        }
        compares++;
        compares++;
        if (!are_exchange) {
            break;
        }
    }
    compares++;
    return compares;
}

int bubbleSort_improve2 (int *array, int size) {
    int compares = 0;
    int exchange_ind = 0;
    int cur_exchange_ind = size-1;
    for (int n = 0; n < size - 1; n++, compares++) {
        for (int i = size - 1; i > exchange_ind; i--, compares++) {
            compares++;
            if (array[i] < array[i-1]) {
                swapInt(array + i, array + i - 1);
                cur_exchange_ind = i;
            }
        }
        compares++;
        exchange_ind = cur_exchange_ind;
    }
    compares++;
    return compares;
}

int shellSort (int *array, int size) {
    int compares = 0;
    int amount_of_repeats = logarithm(size, 3, 0) - 1;
    int h = 1;
    for (int i = 1; i < amount_of_repeats; i++, compares++) {
        h = 3*h + 1;
    }
    compares++;
    while (h > 0) {
        for (int cur_ind = h; cur_ind < size; cur_ind++, compares++) {
            int cur_el = array[cur_ind];
            int insert_ind = cur_ind;
            while (array[insert_ind - h] > cur_el && insert_ind > 0) {
                array[insert_ind] = array[insert_ind - h];
                insert_ind -= h;
                compares+=2;
            }
            compares+=2;
            array[insert_ind] = cur_el;
        }
        compares++;
        h = (h-1) / 3;
        compares++;
    }
    compares++;
    return compares;
}

int quickSort(int *array, int size) {
    int compares = 0;
    int reference_ind = 0;
    int left_ind = 0;
    int right_ind = size - 1;
    while (left_ind <= right_ind) {
        while (array[left_ind] < array[reference_ind] && left_ind < size) {
            left_ind++;
            compares+=2;
        }
        compares+=2;
        while (array[right_ind] > array[reference_ind] && right_ind >= 0) {
            right_ind--;
            compares+=2;
        }
        compares+=2;
        compares++;
        if (left_ind <= right_ind) {
            swapInt(array + left_ind, array + right_ind);
            left_ind++;
            right_ind--;
        }
        compares++;
    }
    compares++;
    compares++;
    if (right_ind > 0) {
        compares += quickSort(array, right_ind + 1);
    }
    compares++;
    if (left_ind < size - 1) {
        compares += quickSort(array + left_ind, size - left_ind);
    }
    return compares;
}

int makeHeap(int *array, int first_ind, int last_ind) {
    int compares = 0;
    int root_el, cur_son_ind, cur_parent_ind;
    root_el = array[first_ind];
    cur_son_ind = 2*first_ind+1;
    cur_parent_ind = first_ind;
    compares+=2;
    if ((cur_son_ind<last_ind) && (array[cur_son_ind]<array[cur_son_ind+1])) {
        cur_son_ind++;
    }
    while ((cur_son_ind<=last_ind) && (root_el<array[cur_son_ind])) {
        swapInt(&array[cur_son_ind], &array[cur_parent_ind]);
        cur_parent_ind = cur_son_ind;
        cur_son_ind = 2*cur_son_ind+1;
        compares+=2;
        if ((cur_son_ind<last_ind) && (array[cur_son_ind]<array[cur_son_ind+1])) {
            cur_son_ind++;
        }
        compares+=2;
    }
    compares+=2;
    return compares;
}

int heapSort(int *array, int size) {
    int compares = 0;
    int first_ind, last_ind;
    first_ind = size/2 ; last_ind = size-1;
    while (first_ind > 0) {
        first_ind = first_ind - 1;
        compares += makeHeap(array, first_ind, last_ind);
        compares++;
    }
    compares++;
    while (last_ind > 0) {
        swapInt(&array[0], &array[last_ind]);
        last_ind--;
        compares += makeHeap(array, first_ind, last_ind);
        compares++;
    }
    compares++;
    return compares;
}

int main () {
    int (*sorting_method[8]) (int*, int) = {insertSort, choiceSort, bubbleSort, bubbleSort_improve1,
                                             bubbleSort_improve2, shellSort, quickSort, heapSort};
    void (*generating_method[8]) (int*, int) = {generateOrderedArray, generateRandomArray, generateOrderedBackwards};

    for (int cur_array_type_ind = 0; cur_array_type_ind < 3; cur_array_type_ind++) {
        for (int cur_size = 5; cur_size <= 45; cur_size += 5) {
            printf("%d\t", cur_size);
        }
        printf("\n");
        for (int cur_method_ind = 0; cur_method_ind < 8; cur_method_ind++) {
            for (int cur_size = 5; cur_size <= 45; cur_size += 5) {
                int test_array[cur_size];
                generating_method[cur_array_type_ind](test_array, cur_size);
                printf("%d\t", sorting_method[cur_method_ind](test_array, cur_size));
            }
            printf("\n");
        }
        printf("\n");
    }
}