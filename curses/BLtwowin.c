#include "curses/BLtwowin.h"
#include "base/BLbase.h"
#include <errno.h>

static BLdisplay2w_t display =
{
    0, 0, 0, 0, 0, 0, // window sizes
    { NULL, NULL, NULL, NULL, NULL, NULL } // WINDOW ptr
};

#define SETUP_WINDOW(yn, y0, id, color, window_name) \
if (NULL == (display.window[id] = derwin(wmain, yn, display.cx, y0, 0))) { \
    fprintf(stderr, "fail to create %s window\n", window_name); \
} \
wbkgd(display.window[id], COLOR_PAIR(color)); \
wclear(display.window[id]); \
wrefresh(display.window[id])

pcBLdisplay2w_t BLdisplay2w_init()
{
    WINDOW* wmain = display.window[BLwinID_main] = initscr();
    start_color();
    init_pair(FwhiteBblack, COLOR_WHITE, COLOR_BLACK);
    init_pair(FblackBwhite, COLOR_BLACK, COLOR_WHITE);
    getmaxyx(display.window[BLwinID_main], display.cy, display.cx);
    display.cy_top = display.cy / 2;
    display.cy_bottom = display.cy - display.cy_top;
    display.cy_top_contents = display.cy_top - 1;
    display.cy_bottom_contents = display.cy_bottom - 2;
    SETUP_WINDOW(1, 0, BLwinID_top_title, FblackBwhite, "top title");
    SETUP_WINDOW(display.cy_top_contents, 1, BLwinID_top_contents, FwhiteBblack, "top contents");
    SETUP_WINDOW(1, display.cy_top, BLwinID_bottom_title, FblackBwhite, "bottom title");
    SETUP_WINDOW(display.cy_bottom_contents, display.cy_top + 1, BLwinID_bottom_contents, FwhiteBblack, "bottom contents");
    SETUP_WINDOW(1, display.cy - 1, BLwinID_footer, FblackBwhite, "footer");
    return &display;
}

#pragma region BLdisplay2w_win_subfunc
pBLwin_t BLdisplay2w_win_main()
{
    pBLwin_t p = (pBLwin_t)malloc(sizeof(BLwin_t));
    p->window = display.window[BLwinID_main];
    p->cx = display.cx;
    p->cy = 1;
    wmove(p->window, 0, 0);
    waddstr(p->window, "");
    return p;
}

pBLwin_t BLdisplay2w_win_top_title()
{
    pBLwin_t p = (pBLwin_t)malloc(sizeof(BLwin_t));
    p->window = display.window[BLwinID_top_title];
    p->cx = display.cx;
    p->cy = 1;
    wmove(p->window, 0, 0);
    waddstr(p->window, "");
    return p;
}

pBLwin_t BLdisplay2w_win_top_contents()
{
    pBLwin_t p = (pBLwin_t)malloc(sizeof(BLwin_t));
    p->window = display.window[BLwinID_top_contents];
    p->cx = display.cx;
    p->cy = display.cy_top_contents;
    wmove(p->window, 0, 0);
    waddstr(p->window, "");
    return p;
}

pBLwin_t BLdisplay2w_win_botttom_title()
{
    pBLwin_t p = (pBLwin_t)malloc(sizeof(BLwin_t));
    p->window = display.window[BLwinID_bottom_title];
    p->cx = display.cx;
    p->cy = 1;
    wmove(p->window, 0, 0);
    waddstr(p->window, "");
    return p;
}

pBLwin_t BLdisplay2w_win_bottom_contents()
{
    pBLwin_t p = (pBLwin_t)malloc(sizeof(BLwin_t));
    p->window = display.window[BLwinID_bottom_contents];
    p->cx = display.cx;
    p->cy = display.cy_bottom_contents;
    wmove(p->window, 0, 0);
    waddstr(p->window, "");
    return p;
}

pBLwin_t BLdisplay2w_win_footer()
{
    pBLwin_t p = (pBLwin_t)malloc(sizeof(BLwin_t));
    p->window = display.window[BLwinID_footer];
    p->cx = display.cx;
    p->cy = 1;
    wmove(p->window, 0, 0);
    waddstr(p->window, "");
    return p;
}

typedef pBLwin_t (*BLwin_factory)();
static const BLwin_factory factories[] =
{
    BLdisplay2w_win_main,
    BLdisplay2w_win_top_title,
    BLdisplay2w_win_top_contents,
    BLdisplay2w_win_botttom_title,
    BLdisplay2w_win_bottom_contents,
    BLdisplay2w_win_footer
};
#pragma endregion BLdisplay2w_win_subfunc

pBLwin_t BLdisplay2w_win(BLwinID_t id)
{
    return factories[id]();
}

void BLwin_clear(pBLwin_t win)
{
    wclear(win->window);
    win->x = win->y = 0;
    wrefresh(win->window);
}

int BLwin_showcenter(pBLwin_t win, const char* message)
{
    int err = EXIT_SUCCESS;
    do {
        int ycenter = win->cy / 2;
        int xcenter = win->cx / 2;
        int xbegin = xcenter - strlen(message) / 2;
        int xend = xbegin + strlen(message);
        if ((xbegin < 0) || (xend >= win->cx))
        {
            err = ERANGE;
            break;
        }
        wmove(win->window, ycenter, xbegin);
        waddstr(win->window, message);
        wrefresh(win->window);
    } while (0);
    return err;
}