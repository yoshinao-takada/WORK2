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
\param kernel [in] float array
\param in [in] float array
\param out[out] float array
\return unix errno compatible number
*/
int BLfilter2D_given_kernel(pcBLarray_t kernel, const BL4i32_t kernel_rect, pcBLarray_t in, pBLarray_t* out);

typedef struct {
    BL4i32_t sum_rect; // MAC sum rect
    BL2i32_t strides; // strides[0]: stride of 2D array src0, strides[1]: stride of 2D array src1
} BLMACprop_t, *pBLMACprop_t;
typedef const BLMACprop_t *pcBLMACprop_t;

BL1r32_t BLblockMACf(const BL1r32_t* src0, const BL1r32_t* src1, pcBLMACprop_t macprop);
#ifdef __cplusplus
}
#endif
#endif /* BLFIL2D_H_ */