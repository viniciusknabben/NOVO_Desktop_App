#include "ringbuffer.h"

RingBuffer::RingBuffer()
{
    ringbuffer * tmp = (ringbuffer*)malloc(sizeof(ringbuffer));
    tmp->wr_idx = 0;
    tmp->rd_idx = 0;
    tmp->size = 0;
    return tmp;
}

void RingBuffer::destroy(ringbuffer * f)
{
    free(f);
}

int isFull(ringbuffer * f)
{
    return (f->size == MAXSIZE);
}

int isEmpty(ringbuffer * f)
{
    return (f->size == 0);
}

int rbTamanho(ringbuffer * f){
    return f->size;
}

int insert(ringbuffer * f, uchar8 d){
    if(isFull(f))
        return 0;
    f->buffer[f->wr_idx++]=d;
    f->wr_idx %= MAXSIZE;
    f->size++;
    return 1;
}

uchar8 removeByte(ringbuffer * f){
    if(isEmpty(f))
        return 0;
    uchar8 tmp = f->buffer[f->rd_idx++];
    f->rd_idx %= MAXSIZE;
    f->size--;
    return tmp;
}

uint16 removeUint(ringbuffer *f)
{
    if(isEmpty(f) || f->size<2)
        return 0;
    uint16 value;
    uchar8 tmp = f->buffer[f->rd_idx++];
    f->rd_idx %= MAXSIZE;
    f->size--;
    return tmp;
}

/*
void print_rb(RingBuffer * f){
    int i;
    for(i = 0; i < MAXSIZE; i++)
        printf("%3d ", (unsigned int)f->buffer[i]);
    printf("\n");

    for(i = 0; i < (f->rd_idx*4+2); i++)
        printf(" ");
    printf("r\n");

    for(i = 0; i < (f->wr_idx*4+2); i++)
        printf(" ");
    printf("w\n");
}
*/
