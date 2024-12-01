#include <stdio.h>

int main()
{
    float num = 0.8675;
    int digit = 0;
    while ((digit < 24 - 9)) {
        num = num * 2.0;
        printf("%d", (int) num);
        if (num > 1.0) {
            num = num - 1.0;
        }
        digit++;
    }

    char *bin_string = "110111100001010";
    float value = 0;
    float cur_digit_value = 0.5;
    while (*bin_string != '\0') {
        if (*bin_string - '0') {
            value += cur_digit_value;
        }
        cur_digit_value /= 2;
        bin_string += 1;
    }
    printf("%f", value);

    return 0;
}