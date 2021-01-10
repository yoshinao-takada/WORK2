#include    "base/BLbase.h"
#include    "base/BLts.h"
#include    <stdlib.h>
#include    <stdio.h>

int elapsed()
{
    const struct timespec tsleep = { 1, 500000000 }; // = 1.5 seconds
    int err = EXIT_SUCCESS;
    do {
        struct timespec t0, t1;
        BLts_getnow(&t0);
        nanosleep(&tsleep, &t1);
        BLts_getelapsed(&t1, &t0);
        if (t1.tv_sec != tsleep.tv_sec)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        __syscall_slong_t tdiff_ns = t1.tv_nsec - tsleep.tv_nsec;
        if (tdiff_ns > 1000000)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
