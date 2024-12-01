#include <stdio.h>
#include <memory.h>

//Выводит на экран двоичное представление числа типа unsigned char, целого числа в диапазоне от 0 до 255
void PrintByte(unsigned char a) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", a>>i & 1);
    }
    printf(" ");
}

//Выводит на экран двоичное представление переменной по адресу a произвольного типа, занимающей size байт
void PrintVar(void *a, unsigned int size) {
    unsigned char *a_in_chars = (unsigned char *) a;
    for (int i = size - 1; i >= 0; i--) {
        PrintByte(a_in_chars[i]);
    }
}

//Выводит на экран двоичное представление массива длиной array_size по адресу a из элементов произвольного типа, каждый экземпляр которого имеет размер size байт
void PrintArray(void *a, unsigned int type_size, unsigned int array_size) {
    for (int i = 0; i < array_size; i++) {
        PrintVar( a + i*type_size, type_size);
    }
}

//Возвращает длину строки, начинающейся по адресу begin
size_t strlen_(char *begin) {
    char *end = begin;
    while (*end != '\0') {
        end++;
    }
    return end - begin;
}

//Записывает в переменную произвольного типа по адресу a значение, двоичное представление которого записано в строке по адресу s
void GetVar(void *a, char *s) {
    size_t passed_length = 0;
    size_t length = strlen_(s);
    unsigned char s_in_chars[length/8];
    for (int i = 0; i < length/8; i++) {
        s_in_chars[i] = 0;
    }
    while (passed_length < length) {
        s_in_chars[passed_length / 8] += (s[length - passed_length - 1] - '0') << passed_length % 8;
        passed_length++;
    }
    memcpy(a, s_in_chars, length/8 + (length % 8 != 0));
}

//Записывает в массив произвольного типа, каждый экземпляр которого имеет размер type_size байт, по адресу a значение, двоичное представление которого записано в строке по адресу s
void GetArray(void *a, char *s, unsigned int type_size) {
    size_t passed_length = 0;
    size_t length = strlen_(s);
    unsigned char s_in_chars[length/8];
    for (int i = 0; i < length/8; i++) {
        s_in_chars[i] = 0;
    }
    while (passed_length < length) {
        s_in_chars[passed_length / 8] += (s[length - passed_length - 1] - '0') << passed_length % 8;
        passed_length++;
    }
    for (int i = 0; i < length / (8*type_size); i++) {
        memcpy(a + (length / (8*type_size) - i - 1)*type_size, s_in_chars + i*type_size, type_size);
    }
}

int main() {
    signed char num1 = 35;
    signed char num2 = -111;

    long long big_num1 = 7802697;
    long long big_num2 = -585911;

    float array[3] = {35, -49.875, 299.8675};
    PrintVar(&num1, sizeof(signed char));
    printf("\n");
    PrintVar(&num2, sizeof(signed char));
    printf("\n");
    PrintVar(&big_num1, sizeof(long long));
    printf("\n");
    PrintVar(&big_num2, sizeof(long long));
    printf("\n");
    PrintArray(array, sizeof(float), 3);
    printf("\n");

    char *charstring1 = "00100011";
    char *charstring2 = "10010001";
    char *longlongstring1 = "0000000000000000000000000000000000000000011101110000111101001001";
    char *longlongstring2 = "1111111111111111111111111111111111111111111101110000111101001001";
    char *floatarraystring = "010000100000110000000000000000001100001001000111100000000000000001000011100101011110111100001010";

    char char1, char2;
    long long long1, long2;
    float array2[3];

    GetVar(&char1, charstring1);
    GetVar(&char2, charstring2);

    GetVar(&long1, longlongstring1);
    GetVar(&long2, longlongstring2);

    GetArray(array2, floatarraystring, sizeof(float));

    //printf("%d %d \n", char1, char2);
    //printf("%lld %lld \n", long1, long2);
    //printf("%f %f %f", array2[0], array[1], array2[2]);

    return 0;
}
