#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Сохраняет по адресу array массив целых чисел размера size со значениями в диапазоне от -size/2 до size/2, идущими в порядке возрастания с шагом 1
void generateOrderedArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = i - size/2;
    }
}

//Сохраняет по адресу array массив целых чисел размера size со случайными значениями в диапазоне от size/2 до -size/2
void generateRandomArray(int *array, int size) {
    generateOrderedArray(array, size);
    for (size_t i = 0; i < size; i++) {
        int ind1 = rand() % size;
        int ind2 = rand() % size;
        int temp = *(array + ind1);
        *(array + ind1) = *(array + ind2);
        *(array + ind2) = temp;
    }
}

int linearSearch(int *array, int size, int value, int *compares) {
    int cur_pos = 0;
    while (cur_pos < size && array[cur_pos] != value) {
        cur_pos += 1;
        (*compares)+=2;
    }
    (*compares)+=2;
    (*compares)++;
    return (cur_pos == size) ? -1 : cur_pos;
}

int fastLinearSearch(int *array, int size, int value, int *compares) {
    int element_beyond = array[size];
    array[size] = value;
    int cur_pos = 0;
    while (array[cur_pos] != value) {
        cur_pos += 1;
        (*compares)++;
    }
    (*compares)++;
    array[size] = element_beyond;
    (*compares)++;
    return (cur_pos == size) ? -1 : cur_pos;
}

int fastLinearSearchForOrdered(int *array, int size, int value, int *compares) {
    int element_beyond = array[size];
    array[size] = value;
    int cur_pos = 0;
    while (array[cur_pos] < value) {
        cur_pos += 1;
        (*compares)++;
    }
    (*compares)++;
    array[size] = element_beyond;
    (*compares)+=2;
    return (array[cur_pos] != value || cur_pos == size) ? -1 : cur_pos;
}

int binarySearch(int *array, int size, int value, int *compares) {
    int left_board = 0;
    int right_board = size-1;
    int cur_pos = -1;
    while (left_board <= right_board) {
        int middle = (left_board + right_board)/2;
        (*compares)++;
        if (value == array[middle]) {
            cur_pos = middle;
            break;
        }
        else if (value > array[middle]) {
            left_board = middle + 1;
            (*compares)++;
        } else {
            right_board = middle - 1;
            (*compares)++;
        }
        (*compares)++;
    }
    (*compares)++;
    return cur_pos;
}

int blockSearch(int *array, int size, int value, int *compares) {
    int step = sqrt(size);
    int cur_pos = 0;
    while (cur_pos <= size - step) {
        (*compares)++;
        if (value < array[cur_pos + step]) {
            cur_pos += fastLinearSearchForOrdered(array+cur_pos, step, value, compares);
            break;
        }
        cur_pos += step;
        (*compares)++;
    }
    (*compares)++;
    (*compares)+=3;
    if (array[size-1] >= value && array[cur_pos] != value && cur_pos > size - step) {
        cur_pos += fastLinearSearchForOrdered(array + cur_pos, size - cur_pos + 1, value, compares);
    }
    (*compares)++;
    return (array[cur_pos] != value) ? -1 : cur_pos;
}

void printMaxCompares(int (*sort_methods[])(int*, int, int, int*), int methods_amount, void generation_method (int*, int)) {
    for (int cur_method_ind = 0; cur_method_ind < methods_amount; cur_method_ind++) {
        for (int cur_size = 50; cur_size <= 450; cur_size += 50) {
            int test_array[cur_size];
            generation_method(test_array, cur_size);
            int max_compares = 0;
            int cur_compares = 0;
            for (int cur_el_ind = 0; cur_el_ind < cur_size; cur_el_ind++) {
                sort_methods[cur_method_ind](test_array, cur_size, test_array[cur_el_ind], &cur_compares);
                max_compares = (cur_compares > max_compares) ? cur_compares : max_compares;
                cur_compares = 0;
            }
            sort_methods[cur_method_ind](test_array, cur_size, cur_size, &cur_compares);
            max_compares = (cur_compares > max_compares) ? cur_compares : max_compares;
            printf("%d\t", max_compares);
        }
        printf("\n");
    }
}

void printAverageCompares(int (*sort_methods[])(int*, int, int, int*), int methods_amount, void generation_method (int*, int)) {
    for (int cur_method_ind = 0; cur_method_ind < methods_amount; cur_method_ind++) {
        for (int cur_size = 50; cur_size <= 450; cur_size += 50) {
            int test_array[cur_size];
            generation_method(test_array, cur_size);
            long long average_compares = 0;
            int cur_compares = 0;
            for (int cur_el_ind = 0; cur_el_ind < cur_size; cur_el_ind++) {
                sort_methods[cur_method_ind](test_array, cur_size, test_array[cur_el_ind], &cur_compares);
                average_compares += cur_compares;
                cur_compares = 0;
            }
            sort_methods[cur_method_ind](test_array, cur_size, cur_size, &cur_compares);
            average_compares += cur_compares;
            printf("%.2lf\t", (double) average_compares / (cur_size+1));
        }
        printf("\n");
    }
}

int main () {
    int (*searching_method_for_unordered[2]) (int*, int, int, int*) = {linearSearch, fastLinearSearch};
    int (*searching_method_for_ordered[3]) (int*, int, int, int*) = {fastLinearSearchForOrdered, binarySearch, blockSearch};

    printf("Array size:\n");
    for (int cur_size = 50; cur_size <= 450; cur_size += 50) {
        printf("%d\t", cur_size);
    }
    printf("\n");

    printf("Max amount of compares, methods for unordered array:\n");

    printMaxCompares(searching_method_for_unordered, 2, generateRandomArray);

    printf("Max amount of compares, methods for ordered array:\n");
    printMaxCompares(searching_method_for_ordered, 3, generateOrderedArray);

    printf("\nArray size:\n");
    for (int cur_size = 50; cur_size <= 450; cur_size += 50) {
        printf("%d\t", cur_size);
    }
    printf("\n");

    printf("Average amount of compares, methods for unordered array:\n");
    printAverageCompares(searching_method_for_unordered, 2, generateRandomArray);

    printf("Average amount of compares, methods for ordered array:\n");
    printAverageCompares(searching_method_for_ordered, 3, generateOrderedArray);

    return 0;
}