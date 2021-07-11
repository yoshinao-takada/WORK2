#ifndef BLSUBWIN_H_
#define BLSUBWIN_H_
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    // basic mode
    BLsubwin_timeformat_none = 0,
    BLsubwin_timeformat_elapsed = 0x10,
    BLsubwin_timeformat_absolute = 0x20,
    // timestamp format
    BLsubwin_timeformat_ISOtime = 0x00, // hh:mm:dd format
    BLsubwin_timeformat_ISOdatetime = 0x01, // yyyy-MM-dd hh:mm:dd format
    BLsubwin_timeformat_sec = 0x02, // %d(time_t) format
    BLsubwin_timeformat_sec_msec = 0x03, // %d.%03d(timespec) format
    BLsubwin_timeformat_sec_microsec = 0x04, // %d.%06d(timespec) format
    BLsubwin_timeformat_sec_nanosec = 0x05, // %d.%09d(timespec) format
} BLsubwin_timeformat_t;

typedef enum {
    BLsubwin_loglevel_none,
    BLsubwin_loglevel_error,
    BLsubwin_loglevel_warning,
    BLsubwin_loglevel_info,
    BLsubwin_loglevel_debug,
    BLsubwin_loglevel_trace
} BLsubwin_loglevel_t;

typedef struct {
    WINDOW *titlebar;
    WINDOW *contents;
    FILE* logsink;
    char* message_buffer;
    int width, height;
    struct timespec origin;
    BLsubwin_timeformat_t timeformat;
    BLsubwin_loglevel_t loglevel;
} BLsubwin_t, *pBLsubwin_t;
typedef const BLsubwin_t *pcBLsubwin_t;

/*!
\brief put a string and scroll if needed.
*/
void BLsubwin_puts(pBLsubwin_t win, BLsubwin_loglevel_t loglevel, const char* message);

/*!
\brief close the subwindow
*/
void BLsubwin_close(pBLsubwin_t *ppwin);

/*!
\brief render anything by printf() style
*/
#define BLsubwin_printf(win, loglevel, ...) (snprintf(win->message_buffer, win->width, __VA_ARGS__), BLsubwin_puts(win, (loglevel), win->message_buffer))

/*!
\brief realloc message_buffer and render anything by printf() style
*/
#define BLsubwin_printf22(win, loglevel, realloc_size, ...) ((int)realloc(win->message_buffer, realloc_size), BLsubwin_printf(win, loglevel, __VA_ARGS__))

#ifdef __cplusplus
}
#endif
#endif /* BLSUBWIN_H_ */