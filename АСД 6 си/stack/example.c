#include <malloc.h>
#include <memory.h>


#define SizeList 100
typedef void *BaseType;
typedef unsigned ptrel;
typedef struct {
    BaseType MemList[SizeList];
    ptrel ptr;
    unsigned int N; // длина списка
    unsigned int Size;
} List;
typedef List Stack;

int main () {
    Stack st;
    st.Size = sizeof(int);
    for (int i = 0; i < SizeList; i++) {
        st.MemList[i] = malloc(st.Size);
    }
    int a = 3;
    int b = 7;
    int c = -12;
    memcpy(st.MemList[0], &a, st.Size);
    memcpy(st.MemList[1], &b, st.Size);
    memcpy(st.MemList[2], &c, st.Size);

    st.ptr = 1;
    st.N = 3;

    return 0;
}
