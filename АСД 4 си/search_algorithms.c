#include <math.h>
#include <stdio.h>

int linearSearch(int *array, int size, int value) {
    int cur_pos = 0;
    while (cur_pos < size && array[cur_pos] != value) {
        cur_pos += 1;
    }
    return (cur_pos == size) ? -1 : cur_pos;
}

int fastLinearSearch(int *array, int size, int value) {
    int element_beyond = array[size];
    array[size] = value;
    int cur_pos = 0;
    while (array[cur_pos] != value) {
        cur_pos += 1;
    }
    array[size] = element_beyond;
    return (cur_pos == size) ? -1 : cur_pos;
}

int fastLinearSearchForOrdered(int *array, int size, int value) {
    int element_beyond = array[size];
    array[size] = value;
    int cur_pos = 0;
    while (array[cur_pos] < value) {
        cur_pos += 1;
    }
    array[size] = element_beyond;
    return (array[cur_pos] != value || cur_pos == size) ? -1 : cur_pos;
}

int binarySearch(int *array, int size, int value) {
    int left_board = 0;
    int right_board = size-1;
    int cur_pos = -1;
    while (left_board <= right_board) {
        int middle = (left_board + right_board)/2;
        if (value == array[middle]) {
            cur_pos = middle;
            break;
        }
        else if (value > array[middle]) {
            left_board = middle + 1;
        } else {
            right_board = middle - 1;
        }
    }
    return cur_pos;
}

int blockSearch(int *array, int size, int value) {
    int step = sqrt(size);
    int cur_pos = 0;
    while (cur_pos <= size - step) {
        if (value < array[cur_pos + step]) {
            cur_pos += fastLinearSearchForOrdered(array+cur_pos, step, value);
            break;
        }
        cur_pos += step;
    }
    if (array[size-1] >= value && array[cur_pos] != value && cur_pos > size - step) {
        cur_pos += fastLinearSearchForOrdered(array + cur_pos, size - cur_pos, value);
    }
    return (array[cur_pos] != value) ? -1 : cur_pos;
}


int main() {
    int unorderedArray[10] = {8, 9, 1, 4, 2, 7, 10, 0, 6, 5};
    int orderedArray[10] = {0, 2, 3, 4, 7, 8, 10, 13, 14, 15};
    int orderedArray2[9] = {0, 2, 3, 4, 7, 8, 10, 13, 14};

    printf("%d\n", linearSearch(unorderedArray, 10, 2));
    printf("%d\n", linearSearch(unorderedArray, 10, 12));
    printf("%d\n\n", linearSearch(unorderedArray, 10, 3));

    printf("%d\n", fastLinearSearch(unorderedArray, 10, 2));
    printf("%d\n", fastLinearSearch(unorderedArray, 10, 12));
    printf("%d\n\n", fastLinearSearch(unorderedArray, 10, 3));

    printf("%d\n", fastLinearSearch(orderedArray, 10, 13));
    printf("%d\n", fastLinearSearch(orderedArray, 10, 0));
    printf("%d\n", fastLinearSearch(orderedArray, 10, 15));
    printf("%d\n", fastLinearSearch(orderedArray, 10, 12));
    printf("%d\n", fastLinearSearch(orderedArray, 10, 18));
    printf("%d\n\n", fastLinearSearch(orderedArray, 10, -2));

    printf("%d\n", binarySearch(orderedArray, 10, 13));
    printf("%d\n", binarySearch(orderedArray, 10, 0));
    printf("%d\n", binarySearch(orderedArray, 10, 15));
    printf("%d\n", binarySearch(orderedArray, 10, 12));
    printf("%d\n", binarySearch(orderedArray, 10, 18));
    printf("%d\n\n", binarySearch(orderedArray, 10, -2));

    printf("%d\n", blockSearch(orderedArray, 10, 4));
    printf("%d\n", blockSearch(orderedArray, 10, 0));
    printf("%d\n", blockSearch(orderedArray, 10, 15));
    printf("%d\n", blockSearch(orderedArray, 10, 14));
    printf("%d\n", blockSearch(orderedArray, 10, 7));

    printf("%d\n", blockSearch(orderedArray, 10, 12));
    printf("%d\n", blockSearch(orderedArray, 10, 18));
    printf("%d\n\n", blockSearch(orderedArray, 10, -2));

    printf("%d\n", blockSearch(orderedArray2, 9, 7));
    printf("%d\n", blockSearch(orderedArray2, 9, 14));
    printf("%d\n", blockSearch(orderedArray2, 9, 13));

}
