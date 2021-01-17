#include "study/BLconvert.h"
#include    <memory.h>

void BLcopy1u8(void* dst, const void* src, size_t count)
{
    memcpy(dst, src, count);
}

void BLcopy1u16(void* dst, const void* src, size_t count)
{
    memcpy(dst, src, count * sizeof(BL1u16_t));
}

void BLcopy1u32(void* dst, const void* src, size_t count)
{
    memcpy(dst, src, count * sizeof(BL1u32_t));
}
void BLcopy1u64(void* dst, const void* src, size_t count)
{
    memcpy(dst,src, count * sizeof(BL1u64_t));
}

#pragma region extending_element_sizes
#pragma region u_from_u
void BLcopy1u16_from_1u8(void* dst, const void* src, size_t count)
{
    BL1u16_t* dst_ = (BL1u16_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u16_t)(*src_++);
    }
}
void BLcopy1u32_from_1u8(void* dst, const void* src, size_t count)
{
    BL1u32_t* dst_ = (BL1u32_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u32_t)(*src_++);
    }
}
void BLcopy1u64_from_1u8(void* dst, const void* src, size_t count)
{
    BL1u64_t* dst_ = (BL1u64_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u64_t)(*src_++);
    }
}
void BLcopy1u32_from_1u16(void* dst, const void* src, size_t count)
{
    BL1u32_t* dst_ = (BL1u32_t*)dst;
    const BL1u16_t* src_ = (const BL1u16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u32_t)(*src_++);
    }
}
void BLcopy1u64_from_1u16(void* dst, const void* src, size_t count)
{
    BL1u64_t* dst_ = (BL1u64_t*)dst;
    const BL1u16_t* src_ = (const BL1u16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u64_t)(*src_++);
    }
}
void BLcopy1u64_from_1u32(void* dst, const void* src, size_t count)
{
    BL1u64_t* dst_ = (BL1u64_t*)dst;
    const BL1u32_t* src_ = (const BL1u32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u64_t)(*src_++);
    }
}
#pragma endregion
#pragma region i_from_u
void BLcopy1i16_from_1u8(void* dst, const void* src, size_t count)
{
    BL1i16_t* dst_ = (BL1i16_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i16_t)(*src_++);
    }
}
void BLcopy1i32_from_1u8(void* dst, const void* src, size_t count)
{
    BL1i32_t* dst_ = (BL1i32_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i32_t)(*src_++);
    }
}
void BLcopy1i64_from_1u8(void* dst, const void* src, size_t count)
{
    BL1i64_t* dst_ = (BL1i64_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i64_t)(*src_++);
    }
}
void BLcopy1i32_from_1u16(void* dst, const void* src, size_t count)
{
    BL1i32_t* dst_ = (BL1i32_t*)dst;
    const BL1u16_t* src_ = (const BL1u16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i32_t)(*src_++);
    }
}
void BLcopy1i64_from_1u16(void* dst, const void* src, size_t count)
{
    BL1i64_t* dst_ = (BL1i64_t*)dst;
    const BL1u16_t* src_ = (const BL1u16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i64_t)(*src_++);
    }
}
void BLcopy1i64_from_1u32(void* dst, const void* src, size_t count)
{
    BL1i64_t* dst_ = (BL1i64_t*)dst;
    const BL1u32_t* src_ = (const BL1u32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i64_t)(*src_++);
    }
}
#pragma endregion
#pragma region u_from_i
void BLcopy1u16_from_1i8(void* dst, const void* src, size_t count)
{
    BL1u16_t* dst_ = (BL1u16_t*)dst;
    const BL1i8_t* src_ = (const BL1i8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u16_t)__max(0, (*src_));
        src_++;
    }
}
void BLcopy1u32_from_1i8(void* dst, const void* src, size_t count)
{
    BL1u32_t* dst_ = (BL1u32_t*)dst;
    const BL1i8_t* src_ = (const BL1i8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u32_t)__max(0, (*src_));
        src_++;
    }
}
void BLcopy1u64_from_1i8(void* dst, const void* src, size_t count)
{
    BL1u64_t* dst_ = (BL1u64_t*)dst;
    const BL1i8_t* src_ = (const BL1i8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u64_t)__max(0, (*src_));
        src_++;
    }
}
void BLcopy1u32_from_1i16(void* dst, const void* src, size_t count)
{
    BL1u32_t* dst_ = (BL1u32_t*)dst;
    const BL1i16_t* src_ = (const BL1i16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u32_t)__max(0, (*src_));
        src_++;
    }
}
void BLcopy1u64_from_1i16(void* dst, const void* src, size_t count)
{
    BL1u64_t* dst_ = (BL1u64_t*)dst;
    const BL1i16_t* src_ = (const BL1i16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u64_t)__max(0, (*src_));
        src_++;
    }
}
void BLcopy1u64_from_1i32(void* dst, const void* src, size_t count)
{
    BL1u64_t* dst_ = (BL1u64_t*)dst;
    const BL1i32_t* src_ = (const BL1i32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u64_t)__max(0, (*src_));
        src_++;
    }
}
#pragma endregion
#pragma region i_from_i
void BLcopy1i16_from_1i8(void* dst, const void* src, size_t count)
{
    BL1i16_t* dst_ = (BL1i16_t*)dst;
    const BL1i8_t* src_ = (const BL1i8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i16_t)(*src_++);
    }
}
void BLcopy1i32_from_1i8(void* dst, const void* src, size_t count)
{
    BL1i32_t* dst_ = (BL1i32_t*)dst;
    const BL1i8_t* src_ = (const BL1i8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i32_t)(*src_++);
    }
}
void BLcopy1i64_from_1i8(void* dst, const void* src, size_t count)
{
    BL1i64_t* dst_ = (BL1i64_t*)dst;
    const BL1i8_t* src_ = (const BL1i8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i64_t)(*src_++);
    }
}
void BLcopy1i32_from_1i16(void* dst, const void* src, size_t count)
{
    BL1i32_t* dst_ = (BL1i32_t*)dst;
    const BL1i16_t* src_ = (const BL1i16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i32_t)(*src_++);
    }
}
void BLcopy1i64_from_1i16(void* dst, const void* src, size_t count)
{
    BL1i64_t* dst_ = (BL1i64_t*)dst;
    const BL1i16_t* src_ = (const BL1i16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i64_t)(*src_++);
    }
}
void BLcopy1i64_from_1i32(void* dst, const void* src, size_t count)
{
    BL1i64_t* dst_ = (BL1i64_t*)dst;
    const BL1i32_t* src_ = (const BL1i32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i64_t)(*src_++);
    }
}
#pragma endregion
#pragma endregion extending_element_sizes

#pragma region reducing_element_sizes                                                                                                                                                                                                                                                                   
#pragma region u_from_u
void BLcopy1u8_from_1u16(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1u16_t* src_ = (const BL1u16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__min(UINT8_MAX, (*src_));
        src_++;
    }
}
void BLcopy1u8_from_1u32(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1u32_t* src_ = (const BL1u32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__min(UINT8_MAX, (*src_));
        src_++;
    }
}
void BLcopy1u8_from_1u64(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1u64_t* src_ = (const BL1u64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__min(UINT8_MAX, (*src_));
        src_++;
    }
}
void BLcopy1u16_from_1u32(void* dst, const void* src, size_t count)
{
    BL1u16_t* dst_ = (BL1u16_t*)dst;
    const BL1u32_t* src_ = (const BL1u32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u16_t)__min(UINT16_MAX, (*src_));
        src_++;
    }
}
void BLcopy1u16_from_1u64(void* dst, const void* src, size_t count)
{
    BL1u16_t* dst_ = (BL1u16_t*)dst;
    const BL1u64_t* src_ = (const BL1u64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u16_t)__min(UINT16_MAX, (*src_));
        src_++;
    }
}
void BLcopy1u32_from_1u64(void* dst, const void* src, size_t count)
{
    BL1u32_t* dst_ = (BL1u32_t*)dst;
    const BL1u64_t* src_ = (const BL1u64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u32_t)__min(UINT32_MAX, (*src_));
        src_++;
    }
}
#pragma endregion
#pragma region i_from_u
void BLcopy1i8_from_1u16(void* dst, const void* src, size_t count)
{
    BL1i8_t* dst_ = (BL1i8_t*)dst;
    const BL1u16_t* src_ = (const BL1u16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i8_t)__max(0, __min(*src_, INT8_MAX));
        src_++;
    }
}
void BLcopy1i8_from_1u32(void* dst, const void* src, size_t count)
{
    BL1i8_t* dst_ = (BL1i8_t*)dst;
    const BL1u32_t* src_ = (const BL1u32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i8_t)__max(0, __min(*src_, INT8_MAX));
        src_++;
    }
}
void BLcopy1i8_from_1u64(void* dst, const void* src, size_t count)
{
    BL1i8_t* dst_ = (BL1i8_t*)dst;
    const BL1u64_t* src_ = (const BL1u64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i8_t)__max(0, __min(*src_, INT8_MAX));
        src_++;
    }
}
void BLcopy1i16_from_1u32(void* dst, const void* src, size_t count)
{
    BL1i16_t* dst_ = (BL1i16_t*)dst;
    const BL1u32_t* src_ = (const BL1u32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i16_t)__max(0, __min(*src_, INT8_MAX));
        src_++;
    }
}
void BLcopy1i16_from_1u64(void* dst, const void* src, size_t count)
{
    BL1i16_t* dst_ = (BL1i16_t*)dst;
    const BL1u64_t* src_ = (const BL1u64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i16_t)__max(0, __min(*src_, INT8_MAX));
        src_++;
    }
}
void BLcopy1i32_from_1u64(void* dst, const void* src, size_t count)
{
    BL1i32_t* dst_ = (BL1i32_t*)dst;
    const BL1u64_t* src_ = (const BL1u64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i32_t)__max(0, __min(*src_, INT8_MAX));
        src_++;
    }
}
#pragma endregion
#pragma region u_from_i
void BLcopy1u8_from_1i16(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1i16_t* src_ = (const BL1i16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__max(0, __min(*src_, UINT8_MAX));
        *src_++;
    }
}
void BLcopy1u8_from_1i32(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1i32_t* src_ = (const BL1i32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__max(0, __min(*src_, UINT8_MAX));
        *src_++;
    }
}
void BLcopy1u8_from_1i64(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1i64_t* src_ = (const BL1i64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__max(0, __min(*src_, UINT8_MAX));
        *src_++;
    }
}
void BLcopy1u16_from_1i32(void* dst, const void* src, size_t count)
{
    BL1u16_t* dst_ = (BL1u16_t*)dst;
    const BL1i32_t* src_ = (const BL1i32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u16_t)__max(0, __min(*src_, UINT8_MAX));
        *src_++;
    }
}
void BLcopy1u16_from_1i64(void* dst, const void* src, size_t count)
{
    BL1u16_t* dst_ = (BL1u16_t*)dst;
    const BL1i64_t* src_ = (const BL1i64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u16_t)__max(0, __min(*src_, UINT8_MAX));
        *src_++;
    }
}
void BLcopy1u32_from_1i64(void* dst, const void* src, size_t count)
{
    BL1u32_t* dst_ = (BL1u32_t*)dst;
    const BL1i64_t* src_ = (const BL1i64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u32_t)__max(0, __min(*src_, UINT8_MAX));
        *src_++;
    }
}
#pragma endregion
#pragma region i_from_i
void BLcopy1i8_from_1i16(void* dst, const void* src, size_t count)
{
    BL1i8_t* dst_ = (BL1i8_t*)dst;
    const BL1i16_t* src_ = (const BL1i16_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i8_t)__max(INT8_MIN, __min(*src_, INT8_MAX));
    }
}
void BLcopy1i8_from_1i32(void* dst, const void* src, size_t count)
{
    BL1i8_t* dst_ = (BL1i8_t*)dst;
    const BL1i32_t* src_ = (const BL1i32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i8_t)__max(INT8_MIN, __min(*src_, INT8_MAX));
    }
}
void BLcopy1i8_from_1i64(void* dst, const void* src, size_t count)
{
    BL1i8_t* dst_ = (BL1i8_t*)dst;
    const BL1i64_t* src_ = (const BL1i64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i8_t)__max(INT8_MIN, __min(*src_, INT8_MAX));
    }
}
void BLcopy1i16_from_1i32(void* dst, const void* src, size_t count)
{
    BL1i16_t* dst_ = (BL1i16_t*)dst;
    const BL1i32_t* src_ = (const BL1i32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i16_t)__max(INT8_MIN, __min(*src_, INT8_MAX));
    }
}
void BLcopy1i16_from_1i64(void* dst, const void* src, size_t count)
{
    BL1i16_t* dst_ = (BL1i16_t*)dst;
    const BL1i64_t* src_ = (const BL1i64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i16_t)__max(INT8_MIN, __min(*src_, INT8_MAX));
    }
}
void BLcopy1i32_from_1i64(void* dst, const void* src, size_t count)
{
    BL1i32_t* dst_ = (BL1i32_t*)dst;
    const BL1i64_t* src_ = (const BL1i64_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1i32_t)__max(INT8_MIN, __min(*src_, INT8_MAX));
    }
}
#pragma endregion
#pragma endregion reducing_element_sizes
