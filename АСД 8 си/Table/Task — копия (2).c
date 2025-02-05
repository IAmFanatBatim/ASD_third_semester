#include "Table.c"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef int T_Value; // Тип значения

int compareKeys(void *E1, void *E2) {
    char *lptr = E1;
    char *rptr = E2;
    while (*lptr == *rptr && *lptr != '\0') {
        lptr++;
        rptr++;
    }
    return *lptr - *rptr;
}

void constructKeyValuePair(void *E, T_Key key, int value) {
    char *kptr = key;
    char *eptr = E;
    for (int i = 0; i < 6; i++) {
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

typedef struct {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа
} WordDescriptor;

char* findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        begin++;
    }
    return begin;
}

char* findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin)) {
        begin++;
    }
    return begin;
}

bool getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void writeWordAsString(WordDescriptor word, char *dest) {
    char *pointer = word.begin;
    while (pointer != word.end) {
        *(dest + (pointer - word.begin)) = *pointer;
        pointer++;
    }
    *(dest + (pointer - word.begin)) = '\0';
}

bool isWordNumber(WordDescriptor word){
    char *pointer = word.begin;
    bool result = true;
    while (pointer != word.end && result) {
        result = isdigit(*pointer);
        pointer++;
    }
    return result;
}

bool isWordIdentifier(WordDescriptor word) {
    char *pointer = word.begin;
    bool result = isalpha(*pointer) || (*pointer) == '_';
    pointer++;
    while (pointer != word.end && result) {
        result = isalpha(*pointer) || (*pointer) == '_' || isdigit(*pointer);
        pointer++;
    }
    return result;
}

bool isPartOfOperator(char c) {
    return !isalpha(c) && c != '_' && !isdigit(c) && c != '{' && c != '}' && c != '[' && c != ']';
}

bool isWordOperator(WordDescriptor word) {
    char *pointer = word.begin;
    bool result = isPartOfOperator(*pointer);
    pointer++;
    while (pointer != word.end && result) {
        result = isPartOfOperator(*pointer);
        pointer++;
    }
    return result;
}

char buffer[1000];
int main() {
    Table table_of_paired;
    InitTable(&table_of_paired, sizeof(T_Value));
    char array_of_paired[10][6] = {"BEGIN", "END", "IF", "THEN", "FOR", "DO", "(", ")", "[", "]"};
    for (int i = 0; i < 5; i++) {
        void *cur_el = malloc(table_of_paired.size);
        constructKeyValuePair(cur_el, array_of_paired[2*i], i+1);
        PutTable(&table_of_paired, cur_el, compareKeys);
        constructKeyValuePair(cur_el, array_of_paired[2*i+1], -i-1);
        PutTable(&table_of_paired, cur_el, compareKeys);
    }
    int counter_of_paired[5] = {0, 0, 0, 0, 0};
    Table table_of_unknown;
    InitTable(&table_of_unknown, sizeof(T_Value));

    char filename[30];
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    int cur = 0;
    while ((buffer[cur] = fgetc(file)) != EOF) {
        cur++;
    }
    buffer[cur] = '\0';
    fclose(file);

    char *cursor = buffer;
    WordDescriptor cur_word;
    bool is_word_found = getWord(cursor, &cur_word);
    while (is_word_found) {
        char *string_word = malloc(cur_word.end - cur_word.begin + 1);
        writeWordAsString(cur_word, string_word);
        void *container = malloc (table_of_paired.size);
        if (ReadTable(&table_of_paired, container, string_word, compareKeys)) {
            int value_of_pair = getTablePairValue(container);
            if (value_of_pair > 0) {
                counter_of_paired[value_of_pair-1]++;
            } else {
                counter_of_paired[-value_of_pair-1]--;
            }
        } else if (!isWordNumber(cur_word) && !isWordIdentifier(cur_word) && !isWordOperator(cur_word)) {
            if (ReadTable(&table_of_unknown, container, string_word, compareKeys)) {
                int frequency = getTablePairValue(container);
                constructKeyValuePair(container, string_word, frequency+1);
                WriteTable(&table_of_unknown, container, string_word, compareKeys);
            } else {
                constructKeyValuePair(container, string_word, 1);
                PutTable(&table_of_unknown, container, compareKeys);
            }
        }
        cursor = cur_word.end;
        is_word_found = getWord(cursor, &cur_word);
    }

    bool has_errors = false;
    for (int i = 0; i < 5; i++) {
        if (counter_of_paired[i] != 0) {
            printf("ERROR! Some constructions <%s - %s> are not closed properly\n", array_of_paired[2*i], array_of_paired[2*i+1]);
            has_errors = true;
        }
    }
    while (!EmptyTable(&table_of_unknown)) {
        void *container_of_unknown = malloc(table_of_unknown.size);
        void *first_string = table_of_unknown.Start->data;
        GetTable(&table_of_unknown, container_of_unknown, first_string, compareKeys);
        int frequency = getTablePairValue(container_of_unknown);
        printf("ERROR! Sequence <%s> is not service word, correct variable name, operator, or number (repeats %d times)\n", first_string, frequency);
        has_errors = true;
    }
    if (!has_errors) {
        printf("Program is correct\n");
    }
}