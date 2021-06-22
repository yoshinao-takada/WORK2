#ifndef BLTEXTUTIL_H_
#define BLTEXTUTIL_H_
#include "base/BLfile.h"
#include "base/BLarray1D.h"
#ifdef __cplusplus
extern "C" {
#endif
/*!
\brief read a text file into a whole text buffer
\param pptext [out] whole text buffer
\param path [in] filepath to the text file
\return errno compatible number
*/
int BLtextutil_readall(void* *pptext, uint32_t* filesize, const char* path);

/*!
\brief read a text file into line buffers
\param pplines [out] multi-line buffer; It should be released by BLSAFEFREE(pplines) later. Refer to note 1 below.
\param path [in] filepath to the text file
\return errno compatible number
*/
int BLtextutil_readfile(pBLarray1D_t* pplines, const char* path);

/*!
\brief count lines in the text
\param text [in]
\return line count
*/
uint32_t BLtextutil_countlines(const char* text, uint32_t textlength);

/*!
\brief split text file into BLarray1D_t
\param text [in]
\param linecount [in]
\return BLarray1D_t with extra text area
*/
pBLarray1D_t BLtextutil_split(char* text, uint32_t textlength);
#ifdef __cplusplus
}
#endif
#endif /* BLTEXTUTIL_H_ */

// note1: multi-line buffer structure
// A BLarray1D_t instance is allocated by BLarray1D_allocex().
// The extra region holds the whole text after replacing the line delimiters with null characters.
// The array1D_t region holds pointers to the beginnings of the text lines.