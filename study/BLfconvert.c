#include    "study/BLfconvert.h"
#include    "base/BLsv.h"

void BLfconvert_r32_from_u8(void* dst, const void* src, size_t count)
{
    BL1r32_t* dst_ = (BL1r32_t*)dst;
    const BL1u8_t* src_ = (const BL1u8_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1r32_t)(*src_++);
    }
}

void BLfconvert_u8_from_r32(void* dst, const void* src, size_t count)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1r32_t* src_ = (const BL1r32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__min(255.0f, __max(0.0f, *src_));
        src_++;
    }
}

/*!
\brief convert float array to uint8_t array, adding offset before casting each element
*/
void BLfconvert_u8_from_r32_offset(void* dst, const void* src, size_t count, float offset)
{
    BL1u8_t* dst_ = (BL1u8_t*)dst;
    const BL1r32_t* src_ = (const BL1r32_t*)src;
    for (size_t i = 0; i < count; i++)
    {
        *dst_++ = (BL1u8_t)__min(255.0f, __max(0.0f, *src_ + offset));
        src_++;
    }
}
