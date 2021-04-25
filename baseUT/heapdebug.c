#include "base/BLheapdebug.h"
#include "base/BLbase.h"
#define SAVEFILE0   BASE_WORK_DIR "heapdebug0.csv"
#define SAVEFILE1   BASE_WORK_DIR "heapdebug1.csv"
#define SAVEFILE2   BASE_WORK_DIR "heapdebug2.csv"
#define BLOCKSIZE0  128
#define BLOCKSIZE1  384
#define BLOCKSIZE2  768

int heapdebug_setup1(void** ppvarray, int arraysize)
{
    int err = EXIT_SUCCESS;
    pBLheapdebug_t work = NULL;
    do {
        if (EXIT_SUCCESS != (err = BLheapdebug_new(128, &work)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLheapdebug_setwork(work);
        BLheapdebug_swap_hooks(&work->apis);
        for (int i = 0; i < arraysize; i++)
        {
            ppvarray[i] = (i < arraysize/2) ? malloc(128) : realloc(ppvarray[i], 128);
        }
        BLheapdebug_swap_hooks(&work->apis);
        BLheapdebug_savecsv(BLheapdebug_getwork(), SAVEFILE0, "w");
        BLheapdebug_swap_hooks(&work->apis);
    } while (0);
    if (err)
    {
        BLSAFEFREE(&work);
    }
    return err;
}

int heapdebug_setup2(void** ppvarray, int arraysize)
{
    int err = EXIT_SUCCESS;
    do {
        for (int i = 0; i < arraysize; i++)
        {
            size_t blocksize = i < arraysize/2 ? BLOCKSIZE1 : BLOCKSIZE0;
            ppvarray[i] = realloc(ppvarray[i], blocksize);
        }
        pBLheapdebug_t p = BLheapdebug_getwork();
        BLheapdebug_swap_hooks(&p->apis);
        BLheapdebug_savecsv(BLheapdebug_getwork(), SAVEFILE1, "w");
        BLheapdebug_swap_hooks(&p->apis);
    } while (0);
    return err;
}

int heapdebug_setup3(void** ppvarray, int arraysize)
{
    int err = EXIT_SUCCESS;
    do {
        for (int i = 0; i < arraysize; i++)
        {
            free(ppvarray[i]);
        }
        pBLheapdebug_t p = BLheapdebug_getwork();
        BLheapdebug_swap_hooks(&p->apis);
        BLheapdebug_savecsv(BLheapdebug_getwork(), SAVEFILE2, "w");
        BLheapdebug_swap_hooks(&p->apis);
    } while (0);
    return err;
}
int heapdebug_cleanup()
{
    int err = EXIT_SUCCESS;
    do {
        pBLheapdebug_t p = BLheapdebug_getwork(); // 
        BLheapdebug_swap_hooks(&p->apis); // restore hook functions
        BLSAFEFREE(&p); // destroy BLheapdebug_t object
        BLheapdebug_setwork(p); // reset BLheapdebug.c/s_workdebug static object
    } while (0);
    return err;
}

int heapdebug()
{
    int err = EXIT_SUCCESS;
    void* pvwork[128] = { NULL };
    do {
        // test malloc()
        if (EXIT_SUCCESS != (err = heapdebug_setup1(pvwork, 16)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        // test realloc()
        if (EXIT_SUCCESS != (err = heapdebug_setup2(pvwork, 16)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }

        // test free()
        if (EXIT_SUCCESS != (err = heapdebug_setup3(pvwork, 16)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        // clean up
        if (EXIT_SUCCESS != (err = heapdebug_cleanup()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
