#include    "study/BLfconvert.h"
#include    "base/BLsv.h"

void BLfconvert_r32_from_u8(BL1r32_t* dst, const BL1u8_t* src, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        *dst++ = (BL1r32_t)(*src++);
    }
}

void BLfconvert_u8_from_r32(BL1u8_t* dst, const BL1r32_t* src, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        *dst++ = (BL1u8_t)__min(255.0f, __max(0.0f, *src));
        src++;
    }
}

void BLfconvert_u8_from_r32_offset(BL1u8_t* dst, const BL1r32_t* src, size_t count, float offset)
{
    for (size_t i = 0; i < count; i++)
    {
        *dst++ = (BL1u8_t)__min(255.0f, __max(0.0f, *src + offset));
        src++;
    }
}
