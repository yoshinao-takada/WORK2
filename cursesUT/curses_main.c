#include "base/BLbase.h"

int mwin();
int vgetl();
int logger();
int multiwin();

int main()
{
    int err = EXIT_SUCCESS;
    do {
        // if (EXIT_SUCCESS != (err = mwin()))
        // {
        //     UT_SHOWBREAK(stderr, "mwin()", 0, err);
        // }
        // if (EXIT_SUCCESS != (err = vgetl()))
        // {
        //     UT_SHOWBREAK(stderr, "vgetl()", 0, err);
        // }
        // if (EXIT_SUCCESS != (err = logger()))
        // {
        //     UT_SHOWBREAK(stderr, "logger()", 0, err);
        // }
        if (EXIT_SUCCESS != (err = multiwin()))
        {
            UT_SHOWBREAK(stderr, "logger()", 0, err);
        }
    } while (0);
    return err;
}