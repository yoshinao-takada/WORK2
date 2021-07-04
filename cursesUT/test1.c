#include <ncurses.h>
#include "curses/BLgetline.h"
#include "curses/BLtwowin.h"
#include <string.h>
#include <strings.h>

int main()
{
    pcBLdisplay2w_t display = BLdisplay2w_init();
    pcBLwin_t footer = BLdisplay2w_win(BLwinID_footer);
    pcBLwin_t contents = BLdisplay2w_win(BLwinID_bottom_contents);
    pBLgetline_t getline = BLgetline_new(32);
    char command[32] = { 0 };
    noecho();
    keypad(stdscr, TRUE);
    while (strcasecmp(command, "quit"))
    {
        while (BLgetlineresult_normal == BLgetline_putc(getline, getch()))
        {
            wmove(footer->window, 0, 0);
            wclear(footer->window);
            waddstr(footer->window, getline->buf);
            wrefresh(footer->window);
        }
        wclear(contents->window);
        wmove(contents->window, 10, 10);
        waddstr(contents->window, getline->buf);
        wrefresh(contents->window);
        strcpy(command, getline->buf);
        BLgetline_clear(getline);
    }
    endwin();
    free((void*)getline);
    return 0;
}