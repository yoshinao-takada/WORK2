#include "base/BLminififo.h"
#include "base/BLbase.h"

static int test_common(pBLminififo_t fifo, uint16_t size)
{
    int err = EXIT_SUCCESS;
    uint8_t *work_buf = NULL;
    uint8_t *ref_buf = NULL;
    do {
        // Step 1: fill up to full
        uint8_t full_size = 0;
        for (uint8_t flag = 0; flag = BLminififo_put(fifo, 0); full_size += flag) ;
        if (size != ((uint16_t)full_size + 1))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        // clear
        fifo->wrptr = fifo->rdptr = 0;

        // Step 2: put, get
        srand(size);
        for (uint16_t i = 0; i < size/2; i++)
        {
            uint8_t data = (uint8_t)rand();
            if (1 != BLminififo_put(fifo, data))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
        srand(size);
        for (uint16_t i = 0; i < size/2; i++)
        {
            uint8_t data_ref = (uint8_t)rand();
            uint8_t data;
            if ((1 != BLminififo_get(fifo, &data)) || (data != data_ref))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
        if (!BLminififo_isempty(fifo))
        {
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }

        // Step 3: puts, gets
        uint16_t data_size = 2 * (size / 3);
        work_buf = (uint8_t*)malloc(data_size);
        ref_buf = (uint8_t*)malloc(data_size);
        if ((work_buf == NULL) || (ref_buf == NULL))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        srand(size - 1u);
        for (uint16_t i = 0; i < data_size; i++)
        {
            ref_buf[i] = (uint8_t)rand();
        }
        if (data_size != (uint16_t)BLminififo_puts(fifo, ref_buf, (uint8_t)data_size))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (data_size != (uint16_t)BLminififo_gets(fifo, work_buf, (uint8_t)data_size))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (!BLminififo_isempty(fifo))
        {
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
        for (uint16_t i = 0; i < data_size; i++)
        {
            if (work_buf[i] != ref_buf[i])
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
    } while (0);
    BLSAFEFREE(&work_buf);
    BLSAFEFREE(&ref_buf);
    return err;
}

int fifo()
{
    int err = EXIT_SUCCESS;
    int err_each = EXIT_SUCCESS;
    do {
        BLminififo64_t fifo64 = BLminififo64_inidef;
        BLminififo128_t fifo128 = BLminififo128_inidef;
        BLminififo256_t fifo256 = BLminififo256_inidef;
        err |= (err_each = test_common(&fifo64.header, 64u));
        err |= (err_each = test_common(&fifo128.header, 128u));
        err |= (err_each = test_common(&fifo256.header, 256u));
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
