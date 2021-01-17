#pragma once
#ifndef BLCONVERT_H_
#define BLCONVERT_H_
#include    "base/BLarray.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*BLcvtkernel)(void* dst, const void* src, size_t count);

typedef struct {
    BLcvtkernel kernel;
    BLcvtkernel param_copier;
    const void* param;
} BLcvt_t, *pBLcvt_t;
typedef const BLcvt_t *pcBLcvt_t;

void BLcopy1u8(void* dst, const void* src, size_t count);
void BLcopy1u16(void* dst, const void* src, size_t count);
void BLcopy1u32(void* dst, const void* src, size_t count);
void BLcopy1u64(void* dst, const void* src, size_t count);
#define BLcopy1i8   BLcopy1u8
#define BLcopy1i16   BLcopy1u16
#define BLcopy1i32   BLcopy1u32
#define BLcopy1i64   BLcopy1u64
#define BLcopy1r32   BLcopy1u32
#define BLcopy1r64   BLcopy1u64

// extending element sizes
void BLcopy1u16_from_1u8(void* dst, const void* src, size_t count);
void BLcopy1u32_from_1u8(void* dst, const void* src, size_t count);
void BLcopy1u64_from_1u8(void* dst, const void* src, size_t count);
void BLcopy1u32_from_1u16(void* dst, const void* src, size_t count);
void BLcopy1u64_from_1u16(void* dst, const void* src, size_t count);
void BLcopy1u64_from_1u32(void* dst, const void* src, size_t count);

void BLcopy1i16_from_1u8(void* dst, const void* src, size_t count);
void BLcopy1i32_from_1u8(void* dst, const void* src, size_t count);
void BLcopy1i64_from_1u8(void* dst, const void* src, size_t count);
void BLcopy1i32_from_1u16(void* dst, const void* src, size_t count);
void BLcopy1i64_from_1u16(void* dst, const void* src, size_t count);
void BLcopy1i64_from_1u32(void* dst, const void* src, size_t count);

void BLcopy1u16_from_1i8(void* dst, const void* src, size_t count);
void BLcopy1u32_from_1i8(void* dst, const void* src, size_t count);
void BLcopy1u64_from_1i8(void* dst, const void* src, size_t count);
void BLcopy1u32_from_1i16(void* dst, const void* src, size_t count);
void BLcopy1u64_from_1i16(void* dst, const void* src, size_t count);
void BLcopy1u64_from_1i32(void* dst, const void* src, size_t count);

void BLcopy1i16_from_1i8(void* dst, const void* src, size_t count);
void BLcopy1i32_from_1i8(void* dst, const void* src, size_t count);
void BLcopy1i64_from_1i8(void* dst, const void* src, size_t count);
void BLcopy1i32_from_1i16(void* dst, const void* src, size_t count);
void BLcopy1i64_from_1i16(void* dst, const void* src, size_t count);
void BLcopy1i64_from_1i32(void* dst, const void* src, size_t count);

// reducing element sizes
void BLcopy1u8_from_1u16(void* dst, const void* src, size_t count);
void BLcopy1u8_from_1u32(void* dst, const void* src, size_t count);
void BLcopy1u8_from_1u64(void* dst, const void* src, size_t count);
void BLcopy1u16_from_1u32(void* dst, const void* src, size_t count);
void BLcopy1u16_from_1u64(void* dst, const void* src, size_t count);
void BLcopy1u32_from_1u64(void* dst, const void* src, size_t count);

void BLcopy1i8_from_1u16(void* dst, const void* src, size_t count);
void BLcopy1i8_from_1u32(void* dst, const void* src, size_t count);
void BLcopy1i8_from_1u64(void* dst, const void* src, size_t count);
void BLcopy1i16_from_1u32(void* dst, const void* src, size_t count);
void BLcopy1i16_from_1u64(void* dst, const void* src, size_t count);
void BLcopy1i32_from_1u64(void* dst, const void* src, size_t count);

void BLcopy1u8_from_1i16(void* dst, const void* src, size_t count);
void BLcopy1u8_from_1i32(void* dst, const void* src, size_t count);
void BLcopy1u8_from_1i64(void* dst, const void* src, size_t count);
void BLcopy1u16_from_1i32(void* dst, const void* src, size_t count);
void BLcopy1u16_from_1i64(void* dst, const void* src, size_t count);
void BLcopy1u32_from_1i64(void* dst, const void* src, size_t count);

void BLcopy1i8_from_1i16(void* dst, const void* src, size_t count);
void BLcopy1i8_from_1i32(void* dst, const void* src, size_t count);
void BLcopy1i8_from_1i64(void* dst, const void* src, size_t count);
void BLcopy1i16_from_1i32(void* dst, const void* src, size_t count);
void BLcopy1i16_from_1i64(void* dst, const void* src, size_t count);
void BLcopy1i32_from_1i64(void* dst, const void* src, size_t count);
#ifdef __cplusplus
}
#endif
#endif /* BLCONVERT_H_ */