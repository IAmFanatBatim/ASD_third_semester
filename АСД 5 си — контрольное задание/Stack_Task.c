#include "Stack_5.h"
#include "Stack_5.c"
#include <assert.h>

//Записывает по адресу result зеркальное отржение строки по адресу source
void *stringReversal (char *source, char *result) {
    char *source_ptr = source;
    Stack for_reversal;
    InitStack(&for_reversal);
    while (*source_ptr != '\0') {
        int cur_el = (int) (*source_ptr);
        PutStack(&for_reversal, cur_el);
        source_ptr++;
    }
    char *result_ptr = result;
    while (!EmptyStack(&for_reversal)) {
        int cur_el;
        GetStack(&for_reversal, &cur_el);
        (*result_ptr) = (char) cur_el;
        result_ptr++;
    }
    *result_ptr = '\0';
}

//возвращает отрицательное значение, если строка lhs располагается до rhs в лексикографическом порядке (как в словаре),
//значение 0, если lhs и rhs равны, иначе – положительное значение.
int strcomp(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *lhs == *rhs) {
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

void Test_stringReversal_Empty() {
    char *s = "";
    char r[1];
    char *model_r = "";
    stringReversal(s, r);
    assert(strcomp(r, model_r) == 0);
}
void Test_stringReversal_SomeText() {
    char *s= "ich liebe dich";
    char r[16];
    char *model_r = "hcid ebeil hci";
    stringReversal(s, r);
    assert(strcomp(r, model_r) == 0);
}
void Test_stringReversal_Equal() {
    char *s = "dennis sinned";
    char r[16];
    char *model_r = "dennis sinned";
    stringReversal(s, r);
    assert(strcomp(r, model_r) == 0);
}

int main() {
    InitMem();
    Test_stringReversal_Empty();
    Test_stringReversal_SomeText();
    Test_stringReversal_Equal();
    printf("All is OK!");
}