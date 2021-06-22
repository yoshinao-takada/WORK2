#include "base/BLptrq.h"
#include <stdlib.h>
#include <errno.h>
#include <memory.h>

pBLptrq_t BLptrq_new(uint16_t size)
{
    size_t cb_head = sizeof(BLptrq_t);
    size_t cb_data = sizeof(void*) * size;
    size_t cb_alloc = cb_head + cb_data;
    pBLptrq_t p = (pBLptrq_t)malloc(cb_alloc);
    if (p)
    {
        p->element_sizes = (size_t*)(p->elements + size);
        p->size = size;
        p->wrpos = p->rdpos = p->reserved = 0;
        for (uint16_t i = 0; i < size; i++)
        {
            p->elements[i] = NULL;
            p->element_sizes[i] = 0;
        }
    }
    return p;    
}

void BLptrq_delete(pBLptrq_t* ppptrq)
{
    if (ppptrq && *ppptrq)
    {
        for (int i = 0; i < (*ppptrq)->size; i++)
        {
            if ((*ppptrq)->elements[i])
            {
                free((*ppptrq)->elements[i]);
            }
        }
        free((void*)(*ppptrq));
        *ppptrq = NULL;
    }
}

int BLptrq_putany(pBLptrq_t q, const void* data, size_t datasize)
{
    int err = EXIT_SUCCESS;
    do {
        uint16_t next_wrpos = (q->wrpos + 1) % q->size;
        if (q->rdpos == next_wrpos)
        {
            err = ENOBUFS;
            break;
        }
        if (NULL == (q->elements[q->wrpos] = (void*)realloc(q->elements[q->wrpos], datasize)))
        {
            err = ENOMEM;
            q->element_sizes[q->wrpos] = 0;
            break;
        }
        q->element_sizes[q->wrpos] = datasize;
        memcpy(q->elements[q->wrpos], data, datasize);
        q->wrpos = next_wrpos;
    } while (0);
    return err;
}

int BLptrq_forceputany(pBLptrq_t q, const void* data, size_t datasize)
{
    int err = EXIT_SUCCESS;
    do {
        uint16_t next_wrpos = (q->wrpos + 1) % q->size;
        if (q->rdpos == next_wrpos)
        {
            q->rdpos = (q->rdpos + 1) % q->size;
        }
        err = BLptrq_putany(q, data, datasize);
    } while (0);
    return err;
}

int BLptrq_puts(pBLptrq_t q, const char* string)
{
    size_t size = strlen(string) + 1;
    return BLptrq_putany(q, (const void*)string, size);
}

int BLptrq_forceputs(pBLptrq_t q, const char* string)
{
    size_t size = strlen(string) + 1;
    return BLptrq_forceputany(q, (const void*)string, size);
}

void BLptrq_getany(pBLptrq_t q, void* data, size_t datasize)
{
    const void* pbuffer = q->elements[q->rdpos];
    memcpy(data, pbuffer, datasize);
    q->rdpos++;
}

int BLptrq_peeksize(pcBLptrq_t q, uint16_t pos, size_t* datasize)
{
    int err = EXIT_SUCCESS;
    do {
        uint16_t peekpos = (q->rdpos + pos) % q->size;
        if (peekpos == q->wrpos)
        {
            err = ENODATA;
            break;
        }
        *datasize = q->element_sizes[peekpos];
    } while (0);
    return err;
}

void BLptrq_peekany(pcBLptrq_t q, uint16_t pos, void* data, size_t datasize)
{
    int peekpos = (int)q->rdpos  - (int)pos;
    while (peekpos < 0)
    {
        peekpos += q->size;
    }
    memcpy(data, q->elements[peekpos], datasize);
}

void Blptrq_dumpall(pcBLptrq_t q, FILE* pf)
{
    fprintf(pf, "(size, wrpos, rdpos)=(%u,%u,%u)\n", q->size, q->wrpos, q->rdpos);
    fprintf(pf, "sizes\telements\n");
    for (size_t i = 0; i < q->size; i++)
    {
        fprintf(pf, "%lu\t0x%08x\n", q->element_sizes[i], (uintptr_t)q->elements[i]);
    }
}
