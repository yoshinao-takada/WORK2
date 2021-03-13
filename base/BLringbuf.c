#include    "base/BLringbuf.h"
#include    "base/BLbase.h"
#include    <errno.h>
#include    <assert.h>

#pragma region ring_buffer_without_exclusive_control
int BLringbuf_new(uint8_t count_bits, pBLringbuf_t* ppobj)
{
    int err = EXIT_SUCCESS;
    do {
        if ((count_bits == 0) || (count_bits > 16))
        {
            err = EINVAL;
            break;
        }
        size_t data_buffer_byte_count = (1 << count_bits);
        size_t head_byte_count = sizeof(BLringbuf_t);
        size_t alloc_byte_count = data_buffer_byte_count + head_byte_count;
        pBLringbuf_t p = (*ppobj = (pBLringbuf_t)malloc(alloc_byte_count));
        if (!p)
        {
            err = ENOMEM;
            break;
        }
        p->mask = (uint16_t)(data_buffer_byte_count - 1);
        p->wrptr = p->rdptr = 0;
    } while (0);
    return err;
}

int BLringbuf_put(pBLringbuf_t obj, uint16_t byte_count, const uint8_t* data, uint16_t* actual)
{
    int err = EXIT_SUCCESS;
    do {
        uint16_t available_space = BLringbuf_available_space(obj);
        if (available_space < byte_count)
        {
            *actual = available_space;
            err = ENOBUFS;
        }
        else
        {
            *actual = byte_count;
        }
        uint16_t actual_copy_byte_count = *actual;
        for (uint16_t i = 0; i < actual_copy_byte_count; i++)
        {
            obj->buffer[obj->wrptr] = data[i];
            obj->wrptr = (obj->wrptr + 1) & obj->mask;
        }
    } while (0);
    return err;
}

int BLringbuf_putforce(pBLringbuf_t obj, uint16_t byte_count, const uint8_t* data)
{
    int err = EXIT_SUCCESS;
    do {
        uint16_t discard_bytes = 0;
        uint16_t available_space = BLringbuf_available_space(obj);
        if (byte_count > available_space)
        {
            err = ENOBUFS;
            discard_bytes = byte_count - available_space;
        }
        for (uint16_t i = 0; i < byte_count; i++)
        {
            if (i < discard_bytes)
            {
                obj->rdptr = (obj->rdptr + 1) & obj->mask;
            }
            obj->buffer[obj->wrptr] = data[i];
            obj->wrptr = (obj->wrptr + 1) & obj->mask;
        }
    } while (0);
    return err;
}

int BLringbuf_get(pBLringbuf_t obj, uint16_t byte_count, uint8_t* data, uint16_t* actual)
{
    int err = EXIT_SUCCESS;
    do {
        uint16_t available_data = BLringbuf_available_data(obj);
        if (available_data < byte_count)
        {
            *actual = available_data;
            err = ENODATA;
        }
        else
        {
            *actual = byte_count;
        }
        uint16_t actual_copy_byte_count = *actual;
        for (uint16_t i = 0; i < actual_copy_byte_count; i++)
        {
            data[i] = obj->buffer[obj->rdptr];
            obj->rdptr = (obj->rdptr + 1) & obj->mask;
        }
    } while (0);
    return err;
}

uint16_t BLringbuf_available_space(pcBLringbuf_t obj)
{
    uint16_t diff = (obj->rdptr - obj->wrptr - 1);
    if (diff & 0x8000)
    {
        diff &= obj->mask;
        diff += (obj->mask + 1);
        diff &= obj->mask;
    }
    return diff; 
}

uint16_t BLringbuf_available_data(pcBLringbuf_t obj)
{
    uint16_t diff = (obj->wrptr - obj->rdptr);
    if (diff & 0x8000)
    {
        diff &= obj->mask;
        diff += (obj->mask + 1);
        diff &= obj->mask;
    }
    return diff;
}

#pragma endregion ring_buffer_without_exclusive_control
#pragma region ring_buffer_with_exclusive_control
int BLringbufex_new(uint8_t count_bits, pBLringbufex_t* ppobj)
{
    assert(*ppobj == NULL);
    int err = EXIT_SUCCESS;
    do {
        if ((count_bits == 0) || (count_bits > 16))
        {
            err = EINVAL;
            break;
        }
        size_t data_buffer_byte_count = (1 << count_bits);
        size_t head_byte_count = sizeof(BLringbufex_t);
        size_t alloc_byte_count = data_buffer_byte_count + head_byte_count;
        pBLringbufex_t p = (*ppobj = (pBLringbufex_t)malloc(alloc_byte_count));
        if (!p)
        {
            err = ENOMEM;
            break;
        }
        p->buf.mask = (uint16_t)(data_buffer_byte_count - 1);
        p->buf.wrptr = p->buf.rdptr = 0;
        err = pthread_mutex_init(&p->mutex, (const pthread_mutexattr_t*)NULL);
    } while (0);
    return err;
}

void BLringbufex_delete(pBLringbufex_t *ppobj)
{
    assert(ppobj && *ppobj);
    pBLringbufex_t p = *ppobj;
    pthread_mutex_destroy(&p->mutex);
    BLSAFEFREE(ppobj);
}

int BLringbufex_lock(pBLringbufex_t obj)
{
    return pthread_mutex_lock(&obj->mutex);
}

int BLringbufex_unlock(pBLringbufex_t obj)
{
    return pthread_mutex_unlock(&obj->mutex);
}
#pragma endregion ring_buffer_with_exclusive_control
