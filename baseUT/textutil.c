#include "base/BLtextutil.h"
#define TEST_FILE_PATH  "/usr/include/ncurses.h"
#define NCURSES_H_0 "/****************************************************************************"
#define NCURSES_H_END "#endif /* __NCURSES_H */"
int textutil()
{
    int err = 0;
    uint32_t filesize = 0;
    uint32_t linecount = 0;
    void* pvtext = NULL;
    pBLarray1D_t lines = NULL;
    do {
        err = BLtextutil_readfile(&pvtext, &filesize, TEST_FILE_PATH);
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        linecount = BLtextutil_countlines((const char*)pvtext, filesize);
        fprintf(stderr, "linecount = %u\n", linecount);
        if (linecount != 1907)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        lines = BLtextutil_split((const char*)pvtext, filesize);
        const void** elements = BLarray1D_begin(lines);
        for (uint16_t iline = lines->size[1] - 4; iline < lines->size[1]; iline++)
        {
            const char* pline = (const char*)elements[iline];
            fprintf(stderr, "%d: %s\n", iline, pline);
        }
        if (0 != strcmp((const char*)elements[0], NCURSES_H_0))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (0 != strcmp((const char*)elements[lines->size[1]-1], NCURSES_H_END))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    BLSAFEFREE(&pvtext);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}