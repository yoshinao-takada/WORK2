#ifndef BLFIL2D_H_
#define BLFIL2D_H_
#include    "base/BLarray.h"
#ifdef __cplusplus
extern "C" {
#endif
/*!
\brief box filter
\param kbox [in] kernel box { TopLeft-x, TopLeft-y, Width, Height } TopLeft: inclusive, Width,Height:exclusive
\param in [in]
\param out[out]
\return unix errno compatible number
*/
int BLfilter2D_box(const BL4i32_t kbox, pcBLarray_t in, pBLarray_t* out);

/*!
\brief arbitrary kernel filter
\param kernel [in]
\param in [in]
\param out[out]
\return unix errno compatible number
*/
int BLfilter2D_given_kernel(pcBLarray_t kernel, pcBLarray_t in, pBLarray_t* out);

/*!
\brief convert uint8_t array to int32_t array
\param in [in] pointer to uint8_t array
\param out[out] pointer-pointer to int32_t array
\return unix errno compatible number
*/
int BLfilter2D_cvtu8i32(pcBLarray_t in, pBLarray_t* out);

/*!
\brief add a constant number to all the elements in a int32_t array
*/
int BLfilter2D_addconsti32(int32_t const_num, pcBLarray_t in, pBLarray_t* out);

/*!
\brief convert int32_t array to uint8_t aray
*/
int BLfilter2D_cvti32u8(pcBLarray_t in, pBLarray_t* out);
#ifdef __cplusplus
}
#endif
#endif /* BLFIL2D_H_ */