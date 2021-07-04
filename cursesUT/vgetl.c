#include "curses/BLgetline.h"
#include "base/BLbase.h"
#include "base/BLdispatcher.h"
#include <memory.h>

/*!
\struct statusbox_t
\brief experimental data structure showing generic status.
*/
typedef struct {
    int status; // any number enumerating a status
    int count; // event counter
    int x0, y0; // reference position in display
    int cx; // display width
    pcBLwin_t display; // display window
    char render_buffer[0];
} statusbox_t, *pstatusbox_t;

static const char* rotating_icons = ROTATING_ICONS_CW;

static pcBLdisplay2w_t display = NULL;
static pcBLwin_t status_display = NULL;
static pcBLwin_t message_box = NULL;
static pcBLwin_t scroll_box = NULL;
static pcBLwin_t input_display = NULL;
static pcBLwin_t titlebar = NULL;
static pBLviewablegetline_t input_box = NULL;
static pstatusbox_t status_box = NULL;

pstatusbox_t statusbox_new(pcBLwin_t win, int y0, int x0, int cx)
{
    size_t cb_alloc = sizeof(statusbox_t) + cx + 1;
    pstatusbox_t p = (pstatusbox_t)malloc(cb_alloc);
    if (!p)
    {
        p->count = p->status = 0;
        p->x0 = x0;
        p->y0 = y0;
        p->cx = cx;
        p->display = win;
        memset(p->render_buffer, 0, cx);
    }
    return p;
}


#pragma region EOL_handler
int EOL_handler(void* context, void* out, const void* in)
{
    pcBLgetline_t getline = (pcBLgetline_t)in;
    pBLwin_t display = (pBLwin_t)out;
    bool* continue_flag = (bool*)context;
    *continue_flag = (bool)strcmp("quit", getline->buf);
    return BLwin_showcenter(display, getline->buf);
}
#pragma endregion

typedef struct {
    pBLwin_t win;
    int counter;
} BLcounterdisplay_t, *pBLcounterdisplay_t;

void* rotate_icon(void* param)
{
    pBLcounterdisplay_t display = (pBLcounterdisplay_t)param;
    wmove(display->win->window, 0, 0);
    waddch(display->win->window, rotating_icons[display->counter]);
    wrefresh(display->win->window);
    display->counter = (display->counter + 1) % strlen(rotating_icons);
    return param;
}

void* show_number(void* param)
{
    pBLcounterdisplay_t display = (pBLcounterdisplay_t)param;
    wprintw(display->win->window, "number = %d\n", display->counter++);
    wrefresh(display->win->window);
    return param;
}

int vgetl()
{
    int err = EXIT_SUCCESS;
    bool continue_flag = true;
    BLcounterdisplay_t rotating_icon_display;
    BLcounterdisplay_t number_display;
    do {
        // initialize display and input objects
        display = BLdisplay2w_init();
        status_display = BLdisplay2w_win(BLwinID_bottom_title);
        message_box = BLdisplay2w_win(BLwinID_bottom_contents);
        scroll_box = BLdisplay2w_win(BLwinID_top_contents);
        scrollok(scroll_box->window, TRUE);
        input_display = BLdisplay2w_win(BLwinID_footer);
        input_box = BLviewablegetline_new(8, input_display, 0, 0);
        status_box = statusbox_new(status_display, 0, 0, 16);
        BLwin_showcenter(BLdisplay2w_win(BLwinID_top_title), "vgetl unit test");

        // init systick dispatcher
        rotating_icon_display = (BLcounterdisplay_t){ BLdisplay2w_win(BLwinID_top_title), 0 };
        number_display = (BLcounterdisplay_t){ BLdisplay2w_win(BLwinID_top_contents), 0 };
        BLdispatcher_core_t cores[] = 
        {
            { 100, 100, rotate_icon, (void*)&rotating_icon_display },
            { 150, 200, show_number, (void*)&number_display }
        };
        struct timespec systick_interval = { 0, 10000000 }; // 10 milliseconds
        if (EXIT_SUCCESS != (err = BLsystickdispatcher_init(ARRAYSIZE(cores), cores, &systick_interval)))
        {
            break;
        }

        // setting EOL handler
        input_box->on_eol = (BLcallbackctx_t)
            { EOL_handler, (void*)&continue_flag, (void*)message_box, (const void*)input_box->getline };

        // main loop
        int i = 0;
        int rotating_position = 0;
        int scroll_limit = scroll_box->cy - 2;
        while (continue_flag)
        {
            int scrollbox_y, scrollbox_x;
            if (BLviewablegetline_getch(input_box) == BLviewablegetlineresult_none)
            {
                continue;
            }
        }
    } while (0);
    endwin();
    return err;
}