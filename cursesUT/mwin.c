#include "curses/BLtwowin.h"
#include "base/BLbase.h"


int mwin()
{
    int err = EXIT_SUCCESS;
    do {
        pcBLdisplay2w_t w = BLdisplay2w_init();
        pcBLwin_t footer = BLdisplay2w_win(BLwinID_footer);
        err = waddstr(footer->window, "Footer");
        if (err == ERR)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        wgetch(footer->window);
        endwin();
    } while (0);
    return err;
}