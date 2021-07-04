#include <ncurses.h>
#include <base/BLdispatcher.h>
#include <curses/BLtwowin.h>
#define SYSTICK_INTERVAL    { 0, 10000000 } /* 10 ms */

typedef struct {
    int counter;
    pcBLwin_t win;
} viewable_counter_t, *pviewwable_counter_t;

static void* update_window(void* pvviewable_counter)
{
    pviewwable_counter_t viewable_counter = (pviewwable_counter_t)pvviewable_counter;
    pcBLwin_t win = viewable_counter->win;
    wclear(win->window);
    wmove(win->window, 0, 0);
    wprintw(win->window, "Count=%04d", viewable_counter->counter++);
    wrefresh(win);
    return pvviewable_counter;
}

typedef struct {
    int bufsize;
    int y, x;
    char buf[0];
} keyin_t, *pkeyin_t;

int main()
{
    pcBLdisplay2w_t display = BLdisplay2w_init();
    pcBLwin_t top_title = BLdisplay2w_win(BLwinID_top_title);
    viewable_counter_t context0 = { 0, top_title };
    BLdispatcher_core_t core0 = { 100, 100, update_window, (void*)&context0 };
}