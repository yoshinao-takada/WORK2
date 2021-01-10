#ifndef UTSAT_H_
#define UTSAT_H_
#include    "study/BLsat.h"
#include    "study/UTcommon.h"

#ifdef __cplusplus
extern "C" {
#endif
/*!
\brief unit test of sammed area table from int8_t to int16_t
*/
int UTsat_i16_from_i8();

/*!
\brief unit test of sammed area table from uint8_t to uint16_t
*/
int UTsat_u16_from_u8();

/*!
\brief unit test of sammed area table from int8_t to int32_t
*/
int UTsat_i32_from_i8();

/*!
\brief unit test of sammed area table from uint8_t to uint32_t
*/
int UTsat_u32_from_u8();

/*!
\brief unit test of sammed area table from float to float
*/int UTsat_r32_from_r32();
#ifdef __cplusplus
}
#endif
#endif /* UTSAT_H_ */