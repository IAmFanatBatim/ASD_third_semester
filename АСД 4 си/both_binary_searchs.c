#include <stdio.h>

int recursiveBinarySearch__(int *array, int size, int value) {
    if (size <= 0) {
        return -1;
    } else {
        int middle_ind = (size-1)/2;
        if (array[middle_ind] == value) {
            return middle_ind;
        } else if (value > array[middle_ind]) {
            return recursiveBinarySearch__(array + middle_ind + 1, size - middle_ind - 1, value);
        } else {
            return recursiveBinarySearch__(array, middle_ind, value);
        }
    }
}

int iterativeBinarySearch(int *array, int size, int value) {
    int left = 0;
    int right = size-1;
    while (left <= right) {
        int middle = (left + right)/2;
        if (array[middle] == value) {
            return middle;
        } else if (value > array[middle]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

int recursiveBinarySearch_(int *array, int left, int right, int value) {
    if (left > right) {
        return -1;
    } else {
        int middle = (left + right)/2;
        if (array[middle] == value) {
            return middle;
        } else if (value > array[middle]) {
            return recursiveBinarySearch_(array, middle + 1, right, value);
        } else {
            return recursiveBinarySearch_(array, left, middle - 1, value);
        }
    }
}

int recursiveBinarySearch(int *array, int size, int value) {
    return recursiveBinarySearch_(array, 0, size-1, value);
}


int main() {
    int orderedArray2[10] = {0, 2, 3, 4, 7, 8, 10, 13, 14, 15};

    printf("%d\n", recursiveBinarySearch(orderedArray2, 10, 13));
    printf("%d\n", recursiveBinarySearch(orderedArray2, 10, 0));
    printf("%d\n", recursiveBinarySearch(orderedArray2, 10, 15));
    printf("%d\n", recursiveBinarySearch(orderedArray2, 10, 12));
    printf("%d\n", recursiveBinarySearch(orderedArray2, 10, 18));
    printf("%d\n\n", recursiveBinarySearch(orderedArray2, 10, -2));

    printf("%d\n", iterativeBinarySearch(orderedArray2, 10, 13));
    printf("%d\n", iterativeBinarySearch(orderedArray2, 10, 0));
    printf("%d\n", iterativeBinarySearch(orderedArray2, 10, 15));
    printf("%d\n", iterativeBinarySearch(orderedArray2, 10, 12));
    printf("%d\n", iterativeBinarySearch(orderedArray2, 10, 18));
    printf("%d\n\n", iterativeBinarySearch(orderedArray2, 10, -2));
}