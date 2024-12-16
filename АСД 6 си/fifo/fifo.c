#if !defined(__FIFO11_C)
#define __FIFO11_C
#include "fifo.h"
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

void InitFifo(Fifo* f, unsigned SizeEl, unsigned SizeBuf) {
    f->Buf = malloc( SizeBuf * sizeof(void*));
    for (int i = 0; i < SizeBuf; i++) {
        f->Buf[i] = malloc(SizeEl);
    }
    f->SizeEl = SizeEl;
    f->SizeBuf = SizeBuf;
    f->Uk1 = 0;
    f->Uk2 = 0;
    f->N = 0;
}

void PutFifo(Fifo *f, void *E) {
    if (f->N == f->SizeBuf) {
        FifoError = FifoOver;
        exit(FifoError);
    } else {
        memcpy(f->Buf[f->Uk2], E, f->SizeEl);
        f->Uk2 = (f->Uk2 + 1) % f->SizeBuf;
        f->N += 1;
        FifoError = FifoOk;
    }
}

void GetFifo(Fifo *f, void *E) {
    if (f->N == 0){
        FifoError = FifoUnder;
        exit(FifoUnder);
    } else {
        memcpy(E, f->Buf[f->Uk1], f->SizeEl);
        f->Uk1 = (f->Uk1 + 1) % f->SizeBuf;
        f->N -= 1;
        FifoError = FifoOk;
    }
}

void ReadFifo(Fifo *f, void *E) {
    if (f->N == 0){
        FifoError = FifoUnder;
        exit(FifoUnder);
    } else {
        memcpy(E, f->Buf[f->Uk1], f->SizeEl);
        FifoError = FifoOk;
    }
}

int EmptyFifo(Fifo *f) {
    return f->N == 0;
}

void DoneFifo(Fifo *f) {
    for (int i = 0; i < f->SizeBuf; i++) {
        free((f->Buf)[i]);
    }
    free(f->Buf);
    f->SizeBuf = 0;
    f->SizeEl = 0;
    f->Uk1 = 0;
    f->Uk2 = 0;
    f->N = 0;
}


#endif
