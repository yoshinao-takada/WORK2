#include    "study/BLsat.h"
#include    <errno.h>

int BLsat_i16_from_i8(pBLarray_t* ppsat, pcBLarray_t src)
{
    int err = EXIT_SUCCESS;
    do {
        BL4u32_t sat_size = BLarray_size2D(int16_t, src->size[1]+1, src->size[2]+1);
        BLarray_alloc(*ppsat, sat_size);
        { // fill top-most row and left-most column with 0
            BL1i16_t* p = (BL1i16_t*)BLarray_begin(*ppsat);
            const int16_t _0 = 0;
            for (uint32_t i = 0; i != (*ppsat)->size[1]; i++)
            {
                p[i] = _0;
            }
            for (uint32_t i = 1; i != (*ppsat)->size[2]; i++)
            {
                uint32_t linear_index = i * (*ppsat)->size[1];
                p[linear_index] = _0;
            }
        }
        BL2u32_t dst_offset = {1,1};
        { // copy src to *ppsat
            BL2u32_t dst_offset = {1,1};
            BL1i16_t* i_dst = (BL1i16_t*)BLarray_at2D(*ppsat, dst_offset);
            const BL1i8_t* i_src = (const BL1i8_t*)BLarray_begin(src);
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    i_dst[ix] = i_src[ix];
                }
                i_dst += (*ppsat)->size[1];
                i_src += src->size[1];
            }
        }
        { // integration
            BL1i16_t* p = (BL1i16_t*)BLarray_at2D(*ppsat, dst_offset);
            ptrdiff_t left = -1;
            ptrdiff_t up = -(ptrdiff_t)(*ppsat)->size[1];
            ptrdiff_t up_left = up + left;
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    *(p + ix) += *(p + ix + up) + *(p + ix + left) - *(p + ix + up_left);
                }
                p += (*ppsat)->size[1];
            }
        }
    } while (0);
    return err;
}

int BLsat_u16_from_u8(pBLarray_t* ppsat, pcBLarray_t src)
{
    int err = EXIT_SUCCESS;
    do {
        BL4u32_t sat_size = BLarray_size2D(uint16_t, src->size[1]+1, src->size[2]+1);
        BLarray_alloc(*ppsat, sat_size);
        { // fill top-most row and left-most column with 0
            BL1u16_t* p = (BL1u16_t*)BLarray_begin(*ppsat);
            const int16_t _0 = 0;
            for (uint32_t i = 0; i != (*ppsat)->size[1]; i++)
            {
                p[i] = _0;
            }
            for (uint32_t i = 1; i != (*ppsat)->size[2]; i++)
            {
                uint32_t linear_index = i * (*ppsat)->size[1];
                p[linear_index] = _0;
            }
        }
        BL2u32_t dst_offset = {1,1};
        { // copy src to *ppsat
            BL2u32_t dst_offset = {1,1};
            BL1u16_t* i_dst = (BL1u16_t*)BLarray_at2D(*ppsat, dst_offset);
            const BL1u8_t* i_src = (const BL1u8_t*)BLarray_begin(src);
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    i_dst[ix] = i_src[ix];
                }
                i_dst += (*ppsat)->size[1];
                i_src += src->size[1];
            }
        }
        { // integration
            BL1u16_t* p = (BL1u16_t*)BLarray_at2D(*ppsat, dst_offset);
            ptrdiff_t left = -1;
            ptrdiff_t up = -(ptrdiff_t)(*ppsat)->size[1];
            ptrdiff_t up_left = up + left;
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    *(p + ix) += *(p + ix + up) + *(p + ix + left) - *(p + ix + up_left);
                }
                p += (*ppsat)->size[1];
            }
        }
    } while (0);
    return err;
}

int BLsat_i32_from_i8(pBLarray_t* ppsat, pcBLarray_t src)
{
    int err = EXIT_SUCCESS;
    do {
        BL4u32_t sat_size = BLarray_size2D(int32_t, src->size[1]+1, src->size[2]+1);
        BLarray_alloc(*ppsat, sat_size);
        { // fill top-most row and left-most column with 0
            BL1i32_t* p = (BL1i32_t*)BLarray_begin(*ppsat);
            const int32_t _0 = 0;
            for (uint32_t i = 0; i != (*ppsat)->size[1]; i++)
            {
                p[i] = _0;
            }
            for (uint32_t i = 1; i != (*ppsat)->size[2]; i++)
            {
                uint32_t linear_index = i * (*ppsat)->size[1];
                p[linear_index] = _0;
            }
        }
        BL2u32_t dst_offset = {1,1};
        { // copy src to *ppsat
            BL2u32_t dst_offset = {1,1};
            BL1i32_t* i_dst = (BL1i32_t*)BLarray_at2D(*ppsat, dst_offset);
            const BL1i8_t* i_src = (const BL1i8_t*)BLarray_begin(src);
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    i_dst[ix] = i_src[ix];
                }
                i_dst += (*ppsat)->size[1];
                i_src += src->size[1];
            }
        }
        { // integration
            BL1i32_t* p = (BL1i32_t*)BLarray_at2D(*ppsat, dst_offset);
            ptrdiff_t left = -1;
            ptrdiff_t up = -(ptrdiff_t)(*ppsat)->size[1];
            ptrdiff_t up_left = up + left;
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    *(p + ix) += *(p + ix + up) + *(p + ix + left) - *(p + ix + up_left);
                }
                p += (*ppsat)->size[1];
            }
        }
    } while (0);
    return err;
}

int BLsat_u32_from_u8(pBLarray_t* ppsat, pcBLarray_t src)
{
    int err = EXIT_SUCCESS;
    do {
        BL4u32_t sat_size = BLarray_size2D(uint32_t, src->size[1]+1, src->size[2]+1);
        BLarray_alloc(*ppsat, sat_size);
        { // fill top-most row and left-most column with 0
            BL1u32_t* p = (BL1u32_t*)BLarray_begin(*ppsat);
            const int32_t _0 = 0;
            for (uint32_t i = 0; i != (*ppsat)->size[1]; i++)
            {
                p[i] = _0;
            }
            for (uint32_t i = 1; i != (*ppsat)->size[2]; i++)
            {
                uint32_t linear_index = i * (*ppsat)->size[1];
                p[linear_index] = _0;
            }
        }
        BL2u32_t dst_offset = {1,1};
        { // copy src to *ppsat
            BL2u32_t dst_offset = {1,1};
            BL1u32_t* i_dst = (BL1u32_t*)BLarray_at2D(*ppsat, dst_offset);
            const BL1u8_t* i_src = (const BL1u8_t*)BLarray_begin(src);
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    i_dst[ix] = i_src[ix];
                }
                i_dst += (*ppsat)->size[1];
                i_src += src->size[1];
            }
        }
        { // integration
            BL1u32_t* p = (BL1u32_t*)BLarray_at2D(*ppsat, dst_offset);
            ptrdiff_t left = -1;
            ptrdiff_t up = -(ptrdiff_t)(*ppsat)->size[1];
            ptrdiff_t up_left = up + left;
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    *(p + ix) += *(p + ix + up) + *(p + ix + left) - *(p + ix + up_left);
                }
                p += (*ppsat)->size[1];
            }
        }
    } while (0);
    return err;
}

int BLsat_r32_from_r32(pBLarray_t* ppsat, pcBLarray_t src)
{
    int err = EXIT_SUCCESS;
    do {
        BL4u32_t sat_size = BLarray_size2D(BL1r32_t, src->size[1]+1, src->size[2]+1);
        BLarray_alloc(*ppsat, sat_size);
        { // fill top-most row and left-most column with 0
            BL1r32_t* p = (BL1r32_t*)BLarray_begin(*ppsat);
            const BL1r32_t _0 = 0.0f;
            for (uint32_t i = 0; i != (*ppsat)->size[1]; i++)
            {
                p[i] = _0;
            }
            for (uint32_t i = 1; i != (*ppsat)->size[2]; i++)
            {
                uint32_t linear_index = i * (*ppsat)->size[1];
                p[linear_index] = _0;
            }
        }
        BL2u32_t dst_offset = {1,1};
        { // copy src to *ppsat
            BL2u32_t dst_offset = {1,1};
            BL1r32_t* i_dst = (BL1r32_t*)BLarray_at2D(*ppsat, dst_offset);
            const BL1r32_t* i_src = (const BL1r32_t*)BLarray_begin(src);
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    i_dst[ix] = i_src[ix];
                }
                i_dst += (*ppsat)->size[1];
                i_src += src->size[1];
            }
        }
        { // integration
            BL1r32_t* p = (BL1r32_t*)BLarray_at2D(*ppsat, dst_offset);
            ptrdiff_t left = -1;
            ptrdiff_t up = -(ptrdiff_t)(*ppsat)->size[1];
            ptrdiff_t up_left = up + left;
            for (uint32_t iy = 0; iy != src->size[2]; iy++)
            {
                for (uint32_t ix = 0; ix != src->size[1]; ix++)
                {
                    *(p + ix) += *(p + ix + up) + *(p + ix + left) - *(p + ix + up_left);
                }
                p += (*ppsat)->size[1];
            }
        }
    } while (0);
    return err;
}

int16_t BLsat_i16_sum(pcBLarray_t sat, const BL4i32_t rect)
{
    const BL1i16_t* i_sat = (const BL1i16_t*)BLarray_at2D(sat, (const BL1u32_t*)rect);
    ptrdiff_t top_right = rect[2];
    ptrdiff_t bottom_left = rect[3] * sat->size[1];
    ptrdiff_t bottom_right = top_right + bottom_left;
    return (i_sat[bottom_right] - i_sat[bottom_left]) - (i_sat[top_right] - i_sat[0]);
}

uint16_t BLsat_u16_sum(pcBLarray_t sat, const BL4i32_t rect)
{
    const BL1u16_t* i_sat = (const BL1u16_t*)BLarray_at2D(sat, (const BL1u32_t*)rect);
    ptrdiff_t top_right = rect[2];
    ptrdiff_t bottom_left = rect[3] * sat->size[1];
    ptrdiff_t bottom_right = top_right + bottom_left;
    return (i_sat[bottom_right] - i_sat[bottom_left]) - (i_sat[top_right] - i_sat[0]);
}

int32_t BLsat_i32_sum(pcBLarray_t sat, const BL4i32_t rect)
{
    const BL1i32_t* i_sat = (const BL1i32_t*)BLarray_at2D(sat, (const BL1u32_t*)rect);
    ptrdiff_t top_right = rect[2];
    ptrdiff_t bottom_left = rect[3] * sat->size[1];
    ptrdiff_t bottom_right = top_right + bottom_left;
    return (i_sat[bottom_right] - i_sat[bottom_left]) - (i_sat[top_right] - i_sat[0]);
}

uint32_t BLsat_u32_sum(pcBLarray_t sat, const BL4i32_t rect)
{
    const BL1u32_t* i_sat = (const BL1u32_t*)BLarray_at2D(sat, (const BL1u32_t*)rect);
    ptrdiff_t top_right = rect[2];
    ptrdiff_t bottom_left = rect[3] * sat->size[1];
    ptrdiff_t bottom_right = top_right + bottom_left;
    return (i_sat[bottom_right] - i_sat[bottom_left]) - (i_sat[top_right] - i_sat[0]);
}


BL1r32_t BLsat_r32_sum(pcBLarray_t sat, const BL4i32_t rect)
{
    const BL1r32_t* i_sat = (const BL1r32_t*)BLarray_at2D(sat, (const BL1u32_t*)rect);
    ptrdiff_t top_right = rect[2];
    ptrdiff_t bottom_left = rect[3] * sat->size[1];
    ptrdiff_t bottom_right = top_right + bottom_left;
    return (i_sat[bottom_right] - i_sat[bottom_left]) - (i_sat[top_right] - i_sat[0]);
}