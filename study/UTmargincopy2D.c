#include    "study/UTmargincopy2D.h"
#include    <opencv2/core.hpp>
#include    <opencv2/imgproc.hpp>
#include    <opencv2/imgcodecs.hpp>
#include    "base/BLfile.h"
#define RANDOM_GRAYSCALE_JPG    WORK_DIR "grayscale_random.jpg"
#define VERTICAL_CYCLIC_CSV     WORK_DIR "vertical_cyclic.csv"
#define FIXED_CSV               WORK_DIR "fixed.csv"
#define EXTEND_CSV              WORK_DIR "extend.csv"
#define CYCLIC_CSV             WORK_DIR "cyclic.csv"

int UTmargincopy2D_vertical_cyclic()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, margined = NULL;
    do {
        BL4u32_t src_size = BLarray_size2D(BL1i32_t, 10, 8);
        BLarray_alloc(src, src_size);
        BL1u32_t* i_src = (BL1u32_t*)BLarray_begin(src);
        for (uint32_t iy = 0; iy != src_size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != src_size[1]; ix++)
            {
                i_src[ix] = 100 * iy + ix;
            }
            i_src += src_size[1];
        }
        BLmarginsetup_t setup = { BLmargintype_vertical_cyclic, { -2, -2, 5, 5 }, NULL };
        err = BLmargincopy_clone(src, &setup, &margined);
        if (EXIT_SUCCESS != (err = BLcommon_save_image(VERTICAL_CYCLIC_CSV, margined, BLimage_save_type_csv_map2D_1u32)))
        { 
            break;
        }
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&margined);
    return err;
}

int UTmargincopy2D_fixed()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, margined = NULL;
    do {
        BL4u32_t src_size = BLarray_size2D(BL1i32_t, 10, 8);
        BLarray_alloc(src, src_size);
        BL1u32_t* i_src = (BL1u32_t*)BLarray_begin(src);
        for (uint32_t iy = 0; iy != src_size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != src_size[1]; ix++)
            {
                i_src[ix] = 100 * iy + ix;
            }
            i_src += src_size[1];
        }
        int32_t margin_value = -128;
        BLmarginsetup_t setup = { BLmargintype_fixed, { -2, -2, 5, 5 }, (const void*)&margin_value };
        err = BLmargincopy_clone(src, &setup, &margined);
        if (EXIT_SUCCESS != (err = BLcommon_save_image(FIXED_CSV, margined, BLimage_save_type_csv_map2D_1u32)))
        { 
            break;
        }
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&margined);
    return err;
}

int UTmargincopy2D_extend()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, margined = NULL;
    do {
        BL4u32_t src_size = BLarray_size2D(BL1i32_t, 10, 8);
        BLarray_alloc(src, src_size);
        BL1u32_t* i_src = (BL1u32_t*)BLarray_begin(src);
        for (uint32_t iy = 0; iy != src_size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != src_size[1]; ix++)
            {
                i_src[ix] = 100 * iy + ix;
            }
            i_src += src_size[1];
        }
        BLmarginsetup_t setup = { BLmargintype_extend, { -2, -2, 5, 5 }, (const void*)NULL };
        err = BLmargincopy_clone(src, &setup, &margined);
        if (EXIT_SUCCESS != (err = BLcommon_save_image(EXTEND_CSV, margined, BLimage_save_type_csv_map2D_1u32)))
        { 
            break;
        }
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&margined);
    return err;
}

int UTmargincopy2D_cyclic()
{
    int err = EXIT_SUCCESS;
    pBLarray_t src = NULL, margined = NULL;
    do {
        BL4u32_t src_size = BLarray_size2D(BL1i32_t, 10, 8);
        BLarray_alloc(src, src_size);
        BL1u32_t* i_src = (BL1u32_t*)BLarray_begin(src);
        for (uint32_t iy = 0; iy != src_size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != src_size[1]; ix++)
            {
                i_src[ix] = 100 * iy + ix;
            }
            i_src += src_size[1];
        }
        BLmarginsetup_t setup = { BLmargintype_cyclic, { -2, -2, 5, 5 }, (const void*)NULL };
        err = BLmargincopy_clone(src, &setup, &margined);
        if (EXIT_SUCCESS != (err = BLcommon_save_image(CYCLIC_CSV, margined, BLimage_save_type_csv_map2D_1u32)))
        { 
            break;
        }
    } while (0);
    BLSAFEFREE(&src);
    BLSAFEFREE(&margined);
    return err;
}
