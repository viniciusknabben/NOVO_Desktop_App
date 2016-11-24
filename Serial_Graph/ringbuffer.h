#ifndef RINGBUFFER_H
#define RINGBUFFER_H

/* Interface da Estrutura de Dados - Fila Circular */

#define MAXSIZE 1000

typedef struct rb_struct ringbuffer;

struct rb_struct
{
    uchar8 buffer[MAXSIZE];
    int rd_idx;
    int wr_idx;
    int size;
};

class RingBuffer
{

private:

    int isFull(ringbuffer * f);

    int isEmpty(ringbuffer * f);


    int size(ringbuffer * f);


    int insert(ringbuffer * f, uchar8 d);

    uchar8 removeByte(ringbuffer * f);

    //void print_rb(ringbuffer * f);

public:
    RingBuffer();
};

#endif // RINGBUFFER_H
