#include <malloc.h>
#include <memory.h>

typedef void *BaseType;
typedef struct {
    BaseType *Buf;
    unsigned SizeBuf; // Максимальная длина очереди
    unsigned SizeEl; // Размер элемента очереди
    unsigned Uk1; // Указатель на «голову» очереди
    unsigned Uk2; // Указатель на «хвост» очереди
    unsigned N;   // Количество элементов очереди
} Fifo;

int main () {
    Fifo fi;
    fi.SizeBuf = 10;
    fi.Buf = malloc(fi.SizeBuf * sizeof(void*));
    fi.SizeEl = sizeof(int);
    for (int i = 0; i < fi.SizeBuf; i++) {
        fi.Buf[i] = malloc(fi.SizeEl);
    }
    int a = 3;
    int b = 7;
    int c = -12;
    memcpy(fi.Buf[3], &a, fi.SizeEl);
    memcpy(fi.Buf[4], &b, fi.SizeEl);
    memcpy(fi.Buf[5], &c, fi.SizeEl);

    fi.Uk1 = 3;
    fi.Uk2 = 6;
    fi.N = 3;

    return 0;
}
