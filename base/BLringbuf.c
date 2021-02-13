#include    "base/BLringbuf.h"
#include    "base/BLbase.h"
#include    <errno.h>

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