#include <stdlib.h>
#include "sort_algorithms.c"
#include <time.h>

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

//Вычисляет разницу между двумя структурами timespec и возвращает ее в формате такой же структуры
struct timespec subtractTimeSpecs(struct timespec start, struct timespec end) {
    struct timespec result;
    result.tv_sec = end.tv_sec - start.tv_sec - (end.tv_nsec < start.tv_nsec);
    result.tv_nsec = 1000000000 * (end.tv_nsec < start.tv_nsec) + end.tv_nsec - start.tv_nsec;
    return result;
}

//Возвращает время сортировки массива array размера size с помощью функции algorithm в формате структуры timespec
struct timespec getTimeOfSorting(int *array, int size, void (*algorithm)(int*, int)) {
    struct timespec time_before, time_after;
    clock_gettime(CLOCK_MONOTONIC, &time_before);
    algorithm(array, size);
    clock_gettime(CLOCK_MONOTONIC, &time_after);
    return subtractTimeSpecs(time_before, time_after);
}

//Выводит на экран представленное структурой timespec время в секундах с точностью до 7 знаков после запятой
void printTimespecs(struct timespec time) {
    printf("%lld,%.7ld", time.tv_sec, time.tv_nsec / 100);
}

int main () {
    void (*sorting_method[8]) (int*, int) = {insertSort, choiceSort, bubbleSort, bubbleSort_improve1,
                                                bubbleSort_improve2, shellSort, quickSort, heapSort};
    void (*generating_method[8]) (int*, int) = {generateOrderedArray, generateRandomArray, generateOrderedBackwards};

    for (int cur_array_type_ind = 0; cur_array_type_ind < 3; cur_array_type_ind++) {
        for (int cur_size = 5; cur_size <= 45; cur_size += 5) {
            printf("%.2d          ", cur_size);
        }
        printf("\n");
        for (int cur_method_ind = 0; cur_method_ind < 8; cur_method_ind++) {
            for (int cur_size = 5; cur_size <= 45; cur_size += 5) {
                int test_array[cur_size];
                generating_method[cur_array_type_ind](test_array, cur_size);
                printTimespecs(getTimeOfSorting(test_array, cur_size, sorting_method[cur_method_ind]));
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
    }
}


