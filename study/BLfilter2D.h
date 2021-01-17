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

#ifdef __cplusplus
}
#endif
#endif /* BLFIL2D_H_ */