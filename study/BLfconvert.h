#pragma once
#ifndef BLFCONVERT_H_
#define BLFCONVERT_H_
#ifdef __cplusplus
#include    <cstdint>
#include    <cstdlib>
extern "C" {
#else
#include    <stdint.h>
#include    <stdlib.h>
#endif
/*!
\brief convert uint8_t array to float array
*/
void BLfconvert_r32_from_u8(BL1r32_t* dst, const BL1u8_t* src, size_t count);

/*!
\brief convert float array to uint8_t array
*/
void BLfconvert_u8_from_r32(BL1u8_t* dst, const BL1r32_t* src, size_t count);

/*!
\brief convert float array to uint8_t array, adding offset before casting each element
*/
void BLfconvert_u8_from_r32_offset(BL1u8_t* dst, const BL1r32_t* src, size_t count, float offset);

#ifdef __cplusplus
}
#endif
#endif /* BLFCONVERT_H_ */