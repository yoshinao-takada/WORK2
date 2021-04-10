#include    "base/BLringbuf.h"
#include    "base/BLbase.h"
#include    <mcheck.h>

int ringbufex()
{
    pBLringbufex_t obj = NULL;
    int err = EXIT_SUCCESS;
    do {
        // create a ringbuffer with mutex as a pointer queue.
        uint16_t least_count = 10;
        uint16_t least_size = sizeof(void*) * least_count;
        err = BLringbufex_newptrqueue(least_count, &obj);
        if (EXIT_SUCCESS != err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        // check buffer size in the ring buffer
        uint16_t available_space = BLringbuf_available_space(&obj->buf);
        if (available_space < least_size)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        uint16_t insufficient_space = (available_space + 1) / 2;
        if (insufficient_space >= least_size)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        // delete the ringbuffer
        BLringbufex_deleteptrqueue(&obj);
    } while (0);
    return err;
}