#include    "study/UTsat.h"
#include    <stdio.h>
#include    <math.h>
#define SRC_CSV WORK_DIR "src.csv"
#define SAT_CSV WORK_DIR "sat.csv"

int UTsat_i16_from_i8()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, sat = NULL;
    do {
        // create the source table filled with random numbers
        srand(0);
        BL4u32_t src_size = BLarray_size2D(int8_t, 16, 20);
        BLarray_alloc(src, src_size);
        uint32_t count = BLprod4(src->size);
        BL1i8_t* p = (BL1i8_t*)BLarray_begin(src);
        do {
            --count;
            *(p + count) = (int8_t)(rand() & 0xff);
        } while (count);

        // create the summed area table under test
        err = BLsat_i16_from_i8(&sat, src);

        // get an areal sum using the summed area table.
        BL4i32_t sum_rect = { 2, 3, 3, 4 };
        int16_t sum_test = BLsat_i16_sum(sat, sum_rect);

        // get an areal sum by adding each elements in the source array
        int16_t sum_ref = 0;
        {
            BL2u32_t scan_begin = { sum_rect[0], sum_rect[1] };
            const BL1i8_t* i_src = (const BL1i8_t*)BLarray_at2D(src, scan_begin);
            for (int32_t iy = 0; iy != sum_rect[3]; iy++)
            {
                for (int32_t ix =0; ix != sum_rect[2]; ix++)
                {
                    sum_ref += (int16_t)i_src[ix];
                }
                i_src += src->size[1];
            }
        }
        // compare the two sums
        err = (sum_ref == sum_test) ? EXIT_SUCCESS : EXIT_FAILURE;
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&sat);
    return err;
}


int UTsat_u16_from_u8()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, sat = NULL;
    do {
        // create the source table filled with random numbers
        srand(0);
        BL4u32_t src_size = BLarray_size2D(uint8_t, 16, 20);
        BLarray_alloc(src, src_size);
        uint32_t count = BLprod4(src->size);
        BL1i8_t* p = (BL1u8_t*)BLarray_begin(src);
        do {
            --count;
            *(p + count) = (uint8_t)(rand() & 0xff);
        } while (count);

        // create the summed area table under test
        err = BLsat_u16_from_u8(&sat, src);

        // get an areal sum using the summed area table.
        BL4i32_t sum_rect = { 2, 3, 3, 4 };
        uint16_t sum_test = BLsat_u16_sum(sat, sum_rect);

        // get an areal sum by adding each elements in the source array
        uint16_t sum_ref = 0;
        {
            BL2u32_t scan_begin = { sum_rect[0], sum_rect[1] };
            const BL1u8_t* i_src = (const BL1u8_t*)BLarray_at2D(src, scan_begin);
            for (int32_t iy = 0; iy != sum_rect[3]; iy++)
            {
                for (int32_t ix =0; ix != sum_rect[2]; ix++)
                {
                    sum_ref += (uint16_t)i_src[ix];
                }
                i_src += src->size[1];
            }
        }
        // compare the two sums
        err = (sum_ref == sum_test) ? EXIT_SUCCESS : EXIT_FAILURE;
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&sat);
    return err;
}

int UTsat_i32_from_i8()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, sat = NULL;
    do {
        // create the source table filled with random numbers
        srand(0);
        BL4u32_t src_size = BLarray_size2D(int8_t, 16, 20);
        BLarray_alloc(src, src_size);
        uint32_t count = BLprod4(src->size);
        BL1i8_t* p = (BL1i8_t*)BLarray_begin(src);
        do {
            --count;
            *(p + count) = (int8_t)(rand() & 0xff);
        } while (count);

        // create the summed area table under test
        err = BLsat_i32_from_i8(&sat, src);

        // get an areal sum using the summed area table.
        BL4i32_t sum_rect = { 2, 3, 3, 4 };
        int32_t sum_test = BLsat_i32_sum(sat, sum_rect);

        // get an areal sum by adding each elements in the source array
        int32_t sum_ref = 0;
        {
            BL2u32_t scan_begin = { sum_rect[0], sum_rect[1] };
            const BL1i8_t* i_src = (const BL1i8_t*)BLarray_at2D(src, scan_begin);
            for (int32_t iy = 0; iy != sum_rect[3]; iy++)
            {
                for (int32_t ix =0; ix != sum_rect[2]; ix++)
                {
                    sum_ref += (int32_t)i_src[ix];
                }
                i_src += src->size[1];
            }
        }
        // compare the two sums
        err = (sum_ref == sum_test) ? EXIT_SUCCESS : EXIT_FAILURE;
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&sat);
    return err;
}


int UTsat_u32_from_u8()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, sat = NULL;
    do {
        // create the source table filled with random numbers
        srand(0);
        BL4u32_t src_size = BLarray_size2D(uint8_t, 2048, 2048);
        BLarray_alloc(src, src_size);
        uint32_t count = BLprod4(src->size);
        BL1i8_t* p = (BL1u8_t*)BLarray_begin(src);
        do {
            --count;
            *(p + count) = (uint8_t)(rand() & 0xff);
        } while (count);

        // create the summed area table under test
        err = BLsat_u32_from_u8(&sat, src);

        // get an areal sum using the summed area table.
        BL4i32_t sum_rect = { 2, 3, 3, 4 };
        uint32_t sum_test = BLsat_u32_sum(sat, sum_rect);

        // get an areal sum by adding each elements in the source array
        uint32_t sum_ref = 0;
        {
            BL2u32_t scan_begin = { sum_rect[0], sum_rect[1] };
            const BL1u8_t* i_src = (const BL1u8_t*)BLarray_at2D(src, scan_begin);
            for (int32_t iy = 0; iy != sum_rect[3]; iy++)
            {
                for (int32_t ix =0; ix != sum_rect[2]; ix++)
                {
                    sum_ref += (uint32_t)i_src[ix];
                }
                i_src += src->size[1];
            }
        }
        // compare the two sums
        err = (sum_ref == sum_test) ? EXIT_SUCCESS : EXIT_FAILURE;
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&sat);
    return err;
}

static int AreEqualR32(float f0, float f1, float ftol)
{
    float absdiff = fabsf(f0 - f1);
    float abssum = fabsf(f0 + f1);
    return (absdiff/abssum) < ftol ? 1:0;
}

int UTsat_r32_from_r32()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, sat = NULL;
    do {
        // create the source table filled with random numbers
        srand(0);
        BL4u32_t src_size = BLarray_size2D(BL1r32_t, 16, 20);
        BLarray_alloc(src, src_size);
        uint32_t count = src_size[1] * src_size[2];
        BL1r32_t* p = (BL1r32_t*)BLarray_begin(src);
        do {
            --count;
            int16_t irand = (int16_t)(rand() & 0xffff);
            *(p + count) = (float)irand;
        } while (count);

        // create the summed area table under test
        err = BLsat_r32_from_r32(&sat, src);

        // get an areal sum using the summed area table.
        BL4i32_t sum_rect = { 2, 3, 3, 4 };
        BL1r32_t sum_test = BLsat_r32_sum(sat, sum_rect);

        // get an areal sum by adding each elements in the source array
        BL1r32_t sum_ref = 0;
        {
            BL2u32_t scan_begin = { sum_rect[0], sum_rect[1] };
            const BL1r32_t* i_src = (const BL1r32_t*)BLarray_at2D(src, scan_begin);
            for (int32_t iy = 0; iy != sum_rect[3]; iy++)
            {
                for (int32_t ix =0; ix != sum_rect[2]; ix++)
                {
                    sum_ref += i_src[ix];
                }
                i_src += src->size[1];
            }
        }
        // compare the two sums
        err = (AreEqualR32(sum_ref, sum_test, 1.0e-6f)) ? EXIT_SUCCESS : EXIT_FAILURE;
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&sat);
    return err;
}
