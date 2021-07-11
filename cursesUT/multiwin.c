#include "curses/BLmultiwin.h"
#include "base/BLbase.h"
static pBLsubwin_t subdisplays[4];
static const char* titles[] = {"Top", "2nd", "3rd", "Bottom"};
static const BLsubwin_timeformat_t timeformats[] = 
{
    BLsubwin_timeformat_sec_msec | BLsubwin_timeformat_elapsed,
    BLsubwin_timeformat_ISOtime | BLsubwin_timeformat_absolute,
    BLsubwin_timeformat_ISOtime | BLsubwin_timeformat_elapsed,
    BLsubwin_timeformat_sec_microsec | BLsubwin_timeformat_elapsed
};
static const BLsubwin_loglevel_t loglevels[] =
{
    BLsubwin_loglevel_trace, BLsubwin_loglevel_debug, BLsubwin_loglevel_info, BLsubwin_loglevel_warning
};

int multiwin()
{
    int err = EXIT_SUCCESS;
    struct timespec sleep_time = { 0, 500000000 }; // 750 ms
    do {
        if (EXIT_SUCCESS != (err = BLmultiwin_init(ARRAYSIZE(subdisplays))))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (int i = 0; i < ARRAYSIZE(subdisplays); i++)
        {
            subdisplays[i] = BLmultiwin_get(i, titles[i], timeformats[i], loglevels[i]);
        }
        for (int j = 0; j < 15; j++)
        {
            for (int i = 0; i < ARRAYSIZE(subdisplays); i++)
            {
                BLsubwin_printf(subdisplays[i], loglevels[i], "j=%d, i=%d\n", j, i);
                nanosleep(&sleep_time, NULL);
            }
        }
        int c = getch();
        endwin();
        for (int i = 0; i < ARRAYSIZE(subdisplays); i++)
        {
            if (EXIT_SUCCESS != (err = BLmultiwin_release(subdisplays[i])))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
        }
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}