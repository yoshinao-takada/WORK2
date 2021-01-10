#ifndef BLSAT_H_
#define BLSAT_H_
#include    "base/BLarray.h"
#ifdef __cplusplus
extern "C" {
#endif
/*!
\brief create a summed area table of int16_t
\param ppsat [out] pointer pointer to the summed area table
\param src [in] pointer to the source table
\return unix errno compatible number
*/
int BLsat_i16_from_i8(pBLarray_t* ppsat, pcBLarray_t src);

/*!
\brief create a summed area table of uint16_t
\param ppsat [out] pointer pointer to the summed area table
\param src [in] pointer to the source table
\return unix errno compatible number
*/
int BLsat_u16_from_u8(pBLarray_t* ppsat, pcBLarray_t src);

/*!
\brief create a summed area table of int32_t
\param ppsat [out] pointer pointer to the summed area table
\param src [in] pointer to the source table
\return unix errno compatible number
*/
int BLsat_i32_from_i8(pBLarray_t* ppsat, pcBLarray_t src);

/*!
\brief create a summed area table of uint32_t
\param ppsat [out] pointer pointer to the summed area table
\param src [in] pointer to the source table
\return unix errno compatible number
*/
int BLsat_u32_from_u8(pBLarray_t* ppsat, pcBLarray_t src);

/*!
\brief create a summed area table of float
\param ppsat [out] pointer pointer to the summed area table
\param src [in] pointer to the source table
\return unix errno compatible number
*/
int BLsat_r32_from_r32(pBLarray_t* ppsat, pcBLarray_t src);


/*!
\brief get a sum over the area
\brief sat [in] summed area table
\brief rect [in] sum area
\return sum over rect
*/
int16_t BLsat_i16_sum(pcBLarray_t sat, const BL4i32_t rect);
uint16_t BLsat_u16_sum(pcBLarray_t sat, const BL4i32_t rect);
int32_t BLsat_i32_sum(pcBLarray_t sat, const BL4i32_t rect);
uint32_t BLsat_u32_sum(pcBLarray_t sat, const BL4i32_t rect);
BL1r32_t BLsat_r32_sum(pcBLarray_t sat, const BL4i32_t rect);

#ifdef __cplusplus
}
#endif
#endif /* BLSAT_H_ */