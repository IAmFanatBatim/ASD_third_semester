#include "Table.c"
#include <assert.h>
#include <stdio.h>

typedef int T_Value;

int compareKeys(void *E1, void *E2) {
    char *lptr = E1;
    char *rptr = E2;
    while (*lptr == *rptr && *lptr != '\0') {
        lptr++;
        rptr++;
    }
    if (*lptr == *rptr) {
        return 0;
    } else {
        return (*lptr > *rptr) ? 1 : -1;
    }
}

void constructKeyValuePair(void *E, T_Key key, int value) {
    char *kptr = key;
    char *eptr = E;
    for (int i = 0; i < sizeof(T_Key); i++) {
        *eptr = *kptr;
        eptr++;
        if (*kptr != '\0') {
            kptr++;
        }
    }
    memcpy(eptr, &value, sizeof(T_Value));
}

T_Value getTablePairValue(void *E) {
    return *(T_Value*)(E+sizeof(T_Key));
}

void Test_InitTable() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    assert(T.Start == NULL && T.ptr == NULL && T.N == 0 && T.size == sizeof(T_Key) + sizeof(T_Value));
}

void Test_PutTable_InEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    assert(PutTable(&T, E, compareKeys));
    assert(compareKeys(T.ptr->data, "Peter") == 0 && getTablePairValue(T.ptr->data) == 3);
}

void Test_PutTable_InNotEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    constructKeyValuePair(E, "Jane", 8);
    assert(PutTable(&T, E, compareKeys));
    assert(compareKeys(T.ptr->data, "Jane") == 0 && getTablePairValue(T.ptr->data) == 8);
}

void Test_PutTable_failed() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    assert(EmptyTable(&T));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    constructKeyValuePair(E, "Peter", 8);
    assert(!PutTable(&T, E, compareKeys));
}

void Test_PutTable() {
    Test_PutTable_InEmpty();
    Test_PutTable_InNotEmpty();
    Test_PutTable_failed();
}

void Test_EmptyTable_IsEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    assert(EmptyTable(&T));
}

void Test_EmptyTable_IsNotEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    assert(!EmptyTable(&T));
}

void Test_EmptyTable() {
    Test_EmptyTable_IsEmpty();
    Test_EmptyTable_IsNotEmpty();
}

void Test_GetTable_failedEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    assert(!GetTable(&T, E, "Peter", compareKeys));
}

void Test_GetTable_failedNotFound() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    assert(!GetTable(&T, E, "Jane", compareKeys));
}

void Test_GetTable_success() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    constructKeyValuePair(E, "Jane", 8);
    PutTable(&T, E, compareKeys);
    void *E2 = malloc(T.size);
    assert(GetTable(&T, E2, "Peter", compareKeys));
    assert(compareKeys(E2, "Peter") == 0 && getTablePairValue(E2) == 3);
}

void Test_GetTable() {
    Test_GetTable_failedEmpty();
    Test_GetTable_failedNotFound();
    Test_GetTable_success();
}

void Test_ReadTable_failedEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    assert(!ReadTable(&T, E, "Peter", compareKeys));
}

void Test_ReadTable_failedNotFound() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    assert(!ReadTable(&T, E, "Jane", compareKeys));
}

void Test_ReadTable_success() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    constructKeyValuePair(E, "Jane", 8);
    PutTable(&T, E, compareKeys);
    void *E2 = malloc(T.size);
    assert(ReadTable(&T, E2, "Peter", compareKeys));
    assert(compareKeys(E2, "Peter") == 0 && getTablePairValue(E2) == 3);
    assert(compareKeys(T.ptr->data, "Peter") == 0 && getTablePairValue(T.ptr->data) == 3);
}

void Test_ReadTable() {
    Test_ReadTable_failedEmpty();
    Test_ReadTable_failedNotFound();
    Test_ReadTable_success();
}

void Test_WriteTable_failedEmpty() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    assert(!WriteTable(&T, E, "Peter", compareKeys));
}

void Test_WriteTable_failedNotFound() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    void *E2 = malloc(T.size);
    constructKeyValuePair(E2, "Jane", 8);
    assert(!WriteTable(&T, E2, "Jane", compareKeys));
}

void Test_WriteTable_success() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    void *E2 = malloc(T.size);
    constructKeyValuePair(E2, "Peter", 8);
    assert(WriteTable(&T, E2, "Peter", compareKeys));
    assert(compareKeys(T.ptr->data, "Peter") == 0 && getTablePairValue(T.ptr->data) == 8);
}

void Test_WriteTable() {
    Test_WriteTable_failedEmpty();
    Test_WriteTable_failedNotFound();
    Test_WriteTable_success();
}

void Test_DoneTable() {
    Table T;
    InitTable(&T, sizeof(T_Value));
    void *E = malloc(T.size);
    constructKeyValuePair(E, "Peter", 3);
    PutTable(&T, E, compareKeys);
    constructKeyValuePair(E, "Jane", 8);
    PutTable(&T, E, compareKeys);
    DoneTable(&T);
    assert(T.size == 0 && T.N == 0 && T.Start == NULL && T.ptr == NULL);
}

void Test_Table() {
    Test_InitTable();
    Test_EmptyTable();
    Test_PutTable();
    Test_GetTable();
    Test_ReadTable();
    Test_WriteTable();
    Test_DoneTable();
}

int main() {
    Test_Table();
    printf("All is OK!");
}