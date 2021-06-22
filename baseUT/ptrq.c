#include "base/BLptrq.h"
#include "base/BLbase.h"
#include "base/BLarray1D.h"
#include <memory.h>
#define QSIZE   4
#define ARRAY1D_SIZE    8

static int ptrq_new_delete();
static int ptrq_putany_getany();

// whole test sequence
int ptrq()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = ptrq_new_delete()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = ptrq_putany_getany()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

// Only new and delete
static int ptrq_new_delete()
{
    int err = EXIT_SUCCESS;
    pBLptrq_t q = NULL;
    do {
        q = BLptrq_new(QSIZE);
        if (!q)
        {
            err  =ENOMEM;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }

    } while (0);
    if (q)
    {
        BLptrq_delete(&q);
    }
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

static pBLarray1D_t random_array()
{
    static const BL2u16_t arraysize = { sizeof(uint32_t), ARRAY1D_SIZE };
    pBLarray1D_t a = NULL;
    BLarray1D_alloc(a, arraysize);
    uint32_t* iter = (uint32_t*)BLarray1D_begin(a);
    for (uint16_t i = 0; i < BLarray1D_elementcount(a); i++)
    {
        *iter++ = rand();
    }
    return a;
}

// put 1D array of eight uint32_t elements
static int ptrq_putany_getany()
{
    static const int seed = 100;
    int err = EXIT_SUCCESS;
    pBLptrq_t q = NULL;
    do {
        q = BLptrq_new(QSIZE);
        if (!q)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = ENOMEM));
        }
        // fill the queue with random arrays
        int i = 0;
        srand(seed);
        for (; i < QSIZE; i++)
        {
            pBLarray1D_t a = random_array();
            err = BLptrq_putany(q, a, BLarray1D_totalbytes(a));
            BLSAFEFREE(&a);
            if (err)
            {
                break;
            }
        }
        if (i != (QSIZE - 1))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        else
        {
            err = EXIT_SUCCESS;
        }
        // retrieve the random arrays and compare their originals
        srand(seed); // reinit RNG
        i = 0;
        for (; i < QSIZE; i++)
        {
            pBLarray1D_t a = random_array();
            size_t datasize = 0;
            if (EXIT_SUCCESS != (err = BLptrq_peeksize(q, 0, &datasize)))
            {
                break;
            }
            if (datasize != BLarray1D_totalbytes(a))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
            pBLarray1D_t b = (pBLarray1D_t)malloc(datasize);
            BLptrq_getany(q, (void*)b, datasize);
            if (memcmp(a, b, datasize))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
        if (i != (QSIZE - 1))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        else
        {
            err = EXIT_SUCCESS;
        }
    } while (0);
    if (q)
    {
        BLptrq_delete(&q);
    }
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
