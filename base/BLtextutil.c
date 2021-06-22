#include "base/BLtextutil.h"

int BLtextutil_readfile(void* *pptext, uint32_t* filesize, const char* path)
{
    int err = EXIT_SUCCESS;
    FILE* pf = NULL;
    do {
        if (EXIT_SUCCESS != (err = BLfile_size(path, filesize)))
        {
            break;
        }
        void* p = (*pptext = malloc(*filesize + 1));
        if (!p)
        {
            break;
        }
        if (EXIT_SUCCESS != (err = BLfile_open(&pf, path, "r")))
        {
            break;
        }
        size_t read_count = fread(p, *filesize, 1, pf);
        if (read_count != 1)
        {
            err = errno;
            break;
        }
        char* pch = (char*)p;
        pch[*filesize] = '\0';
    } while (0);
    if (pf)
    {
        fclose(pf);
    }
    return err;
}

uint32_t BLtextutil_countlines(const char* text, uint32_t textlength)
{
    uint32_t count = 0;
    const char* ptr = text;
    const char* end = ptr + textlength;
    bool onDelimiter = true;
    do {
        if (onDelimiter && *ptr != '\r' && *ptr != '\n')
        {
            count++;
            onDelimiter = false;
        }
        else
        {
            onDelimiter = (*ptr == '\r' || *ptr == '\n');
        }
        ptr++;
    } while (ptr != end);
    return count;
}

pBLarray1D_t BLtextutil_split(char* text, uint32_t textlength)
{
    uint32_t linecount = BLtextutil_countlines(text, textlength);
    pBLarray1D_t p = NULL;
    BL2u16_t arraysize = { (uint16_t)sizeof(void*), (uint16_t)linecount };
    BLarray1D_allocex(p, arraysize, textlength);
    if (!p)
    {
        return p;
    }
    char* textBegin = (char*)p + BLarray1D_totalbytes(p);
    memcpy(textBegin, text, textlength);
    char** iterator = (char**)BLarray1D_begin(p);
    bool onDelimiter = true;
    char* ptr = textBegin;
    const char* textEnd = textBegin + textlength;
    do {
        if (onDelimiter && *ptr != '\r' && *ptr != '\n')
        {
            *iterator = ptr;
            iterator++;
            onDelimiter = false;
        }
        else
        {
            onDelimiter = (*ptr == '\r' || *ptr == '\n');
        }
        if (*ptr < ' ')
        {
            *ptr = '\0';
        }
        ptr++;
    } while (ptr != textEnd);
    return p;
}
