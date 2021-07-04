#ifndef BLdisplay2w_H_
#define BLdisplay2w_H_
#include <stdint.h>
#include <ncurses.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FwhiteBblack = 1, // foreground: white, background: black
    FblackBwhite = 2 // foreground: black, background: white
} BLcolors_t;

typedef enum {
    BLwinID_main,
    BLwinID_top_title,
    BLwinID_top_contents,
    BLwinID_bottom_title,
    BLwinID_bottom_contents,
    BLwinID_footer
} BLwinID_t;

// window-base framework object
typedef struct {
    // window size parameters
    int cx, cy; // main widow size
    int cy_top; // top window height including header
    int cy_bottom; // bottom window height including header and footer
    int cy_top_contents; // top window content area height
    int cy_bottom_contents; // bottom window content area height

    // window object pointers
    WINDOW* window[BLwinID_footer + 1];
} BLdisplay2w_t, *pBLdisplay2w_t;
typedef const BLdisplay2w_t *pcBLdisplay2w_t;

/*!
\brief create a new window-base framework object
*/
pcBLdisplay2w_t BLdisplay2w_init();

// I/F object of each subwindow
typedef struct {
    WINDOW* window;
    int cx, cy;
    int y, x; // cursor position
} BLwin_t, *pBLwin_t;
typedef const BLwin_t *pcBLwin_t;

/*!
\brief get a window I/F object
\param id [in] Window ID
\return object pointer
*/
pBLwin_t BLdisplay2w_win(BLwinID_t id);

/*!
\brief clear the window
*/
void BLwin_clear(pBLwin_t win);

/*!
\brief show a short message at the center of the window
\param win [in] window
\param message [in] message to show
\return EXIT_SUCCESS or ERANGE
*/
int BLwin_showcenter(pBLwin_t win, const char* message);
#ifdef __cplusplus
}
#endif
#endif /* BLdisplay2w_H_ */