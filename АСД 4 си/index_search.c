#include <stdbool.h>
#include <stdio.h>

int logarithm (int base, int num, bool is_ceil) {
    int cur_num = 1;
    int cur_result = 0;
    while (cur_num < num) {
        cur_num *= base;
        cur_result++;
    }
    if (!is_ceil) {
        return cur_result - (cur_num > num);
    } else {
        return cur_result;
    }
}

int degree (int base, int d) {
    int result = 1;
    for (int i = 0; i < d; i++) {
        result *= base;
    }
    return result;
}

int get_cur_index(int size, int num, int level) {
    int left = 0;
    int right = size - 1;
    while (level > 0 && (right >= left)) {
        int middle = (left + right) / 2;
        if (num >> (level - 1) & 1) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
        level--;
    }
    return (right >= left) ? right : -1;
}

int main () {
    for (int n = 8; n <= 14; n++) {
        printf("n = %d;\t indexes: ", n);

        int level = logarithm(2, n+1, false);
        int parts_amount = degree(2, level);

        for (int cur = 0; cur < parts_amount; cur++) {
            int cur_index = get_cur_index(n, cur, level);
            if (cur_index != -1) {
                printf("%d, ", get_cur_index(n, cur, level));
            }
        }
        printf("\b\b \n");
    }
}