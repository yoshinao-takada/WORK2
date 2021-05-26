#include    "base/BLminififo.h"
#include    <malloc.h>
pBLminififo_t BLminififo_new(BLminififotype_t type)
{
    static const BLminififo64_t template64 = BLminififo64_inidef;
    static const BLminififo128_t template128 = BLminififo128_inidef;
    static const BLminififo256_t template256 = BLminififo256_inidef;
    pBLminififo_t p = NULL;
    switch (type)
    {
        case BLminififo64:
        {
            pBLminififo64_t px = (pBLminififo64_t)malloc(sizeof(BLminififo64_t));
            if (px) memcpy(px, &template64, sizeof(BLminififo64));
            p = &px->header;
            break;
        }
        case BLminififo128:
        {
            pBLminififo128_t px = (pBLminififo128_t)malloc(sizeof(BLminififo128_t));
            if (px) memcpy(px, &template128, sizeof(BLminififo128));
            p = &px->header;
            break;
        }
        case BLminififo256:
        {
            pBLminififo256_t px = (pBLminififo256_t)malloc(sizeof(BLminififo256_t));
            if (px) memcpy(px, &template256, sizeof(BLminififo256));
            p = &px->header;
            break;
        }
    }
    return p;
}

uint8_t BLminififo_put(pBLminififo_t fifo, uint8_t data)
{
    uint8_t prcoessed_byte_count = 0;
    pBLminififo256_t fifo_ = (pBLminififo256_t)fifo;
    fifo_->buffer[fifo->wrptr] = data;
    uint8_t next_wrptr = (fifo->wrptr + 1) & fifo->mask;
    if (next_wrptr != fifo->rdptr)
    {
        prcoessed_byte_count++;
        fifo->wrptr = next_wrptr;
    }
    return prcoessed_byte_count;
}

uint8_t BLminififo_get(pBLminififo_t fifo, uint8_t* data)
{
    uint8_t processed_byte_count = 0;
    pBLminififo256_t fifo_ = (pBLminififo256_t)fifo;
    if (fifo->rdptr != fifo->wrptr)
    {
        *data = fifo_->buffer[fifo->rdptr];
        fifo->rdptr = fifo->mask & (fifo->rdptr + 1);
        processed_byte_count = 1;
    }
    return processed_byte_count;
}

uint8_t BLminififo_puts(pBLminififo_t fifo, const uint8_t*data, uint8_t count)
{
    uint8_t processed_byte_count = 0;
    for (uint8_t i = 0; i < count; i++)
    {
        if (BLminififo_put(fifo, data[i]))
        {
            processed_byte_count++;
        }
        else
        {
            break;
        }
    }
    return processed_byte_count;
}

uint8_t BLminififo_gets(pBLminififo_t fifo, uint8_t*data, uint8_t count)
{
    uint8_t processed_byte_count = 0;
    for (uint8_t i = 0; i < count; i++)
    {
        if (BLminififo_get(fifo, &data[i]))
        {
            processed_byte_count++;
        }
        else
        {
            break;
        }
    }
    return processed_byte_count;
}

void BLminififo_cancel(pBLminififo_t fifo)
{
    fifo->wrptr = (fifo->wrptr - 1) & fifo->mask;
}

uint8_t BLminififo_lock(pBLminififo_t fifo)
{
    ///
    /// disable interrupt
    ///
    uint8_t locked = ++(fifo->locker);
    if (locked > 1)
    {
        --(fifo->locker);
        locked = 0;
    }
    ///
    /// enable interrupt
    ///
    return locked;
}
