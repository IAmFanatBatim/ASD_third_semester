#include "Table.c"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int compareKeys(void *E1, void *E2) {
    char *lptr = E1;
    char *rptr = E2;
    while (*lptr == *rptr && *lptr != '\0') {
        lptr++;
        rptr++;
    }
    return *lptr - *rptr;
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
    //printf("ATTENTION! %d\n", *(&value));
    memcpy(eptr, &value, sizeof(int));
}

char buffer[1000];
int main() {
    Table paired_words;
    InitTable(&paired_words, sizeof(int));
    char all_words[10][6] = {"BEGIN", "END", "IF", "THEN", "FOR", "DO", "(", ")", "[", "]"};
    for (int i = 0; i < 5; i++) {
        //printf("CYCLE START! %d\n", i);
        void *cur_el = malloc(sizeof(int) + sizeof(T_Key));
        constructKeyValuePair(cur_el, all_words[2*i], i+1);
        //printf("ATTENTION2! %s %s\n", all_words[2*i], cur_el);
        //printf("%d? ", PutTable(&paired_words, cur_el, compareKeys));
        PutTable(&paired_words, cur_el, compareKeys);

        constructKeyValuePair(cur_el, all_words[2*i+1], -i-1);
        //printf("ATTENTION2! %s %s\n", all_words[2*i+1], cur_el);
        //printf("%d? ", PutTable(&paired_words, cur_el, compareKeys));
        PutTable(&paired_words, cur_el, compareKeys);
    }
    int counter_of_paired[5] = {0, 0, 0, 0, 0};
    char filename[30];
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    int cur = 0;
    while ((buffer[cur] = fgetc(fp)) != EOF) {
        cur++;
    }
    buffer[cur] = '\0';
    fclose(fp);

    char *cursor = buffer;
    WordDescriptor cur_word;
    bool flag2 = getWord(cursor, &cur_word);
    bool has_errors = false;
    while (flag2) {
        //printWord(cur_word);
        char *string_word = malloc(cur_word.end - cur_word.begin + 1);
        writeWordAsString(cur_word, string_word);
        //printf("|%s|\n", string_word);
        void *container = malloc (sizeof(T_Key) + sizeof(int));
        if (ReadTable(&paired_words, container, string_word, compareKeys)) {
            //printf("It's table string! \t");
            int cur_value = *((int*)(container+sizeof(T_Key)));
            //printf("%d %d %lu %lu %s\t", cur_value, sizeof(T_Key), container, container+sizeof(T_Key), container);
            if (cur_value > 0) {
                counter_of_paired[cur_value-1]++;
            } else {
                counter_of_paired[-cur_value-1]--;
            }
            //printf("Table string proceeded!\n");
        } else if (!isWordNumber(cur_word) && !isWordIdentifier(cur_word) && !isWordOperator(cur_word)) {
            //printf("Unknown sequence found!\n");
            printf("ERROR! Sequence <%s> is not service word, correct variable name, operator, or number\n", string_word);
            has_errors = true;
        } else {
            //printf("Vsyo idet po planu!\n");
        }
        cursor = cur_word.end;
        flag2 = getWord(cursor, &cur_word);
    }
    for (int i = 0; i < 5; i++) {
        //printf("%d ", counter_of_paired[i]);
        if (counter_of_paired[i] != 0) {
            printf("ERROR! Some constructions <%s - %s> are not closed properly\n", all_words[2*i], all_words[2*i+1]);
            has_errors = true;
        }
    }
    if (!has_errors) {
        printf("Programm is correct\n");
    }
}