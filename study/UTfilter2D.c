#include    "study/UTfilter2D.h"
#include    "study/BLfilter2D.h"
#define BEFORE_BOX_JPG      WORK_DIR "before-box.jpg"
#define AFTER_BOX_JPG       WORK_DIR "after-box.jpg"
int UTfilter2D_box()
{
    int err = EXIT_SUCCESS;
    pBLarray_t before = NULL, after = NULL;
    do {
        BL4i32_t kbox = { -2, -2, 5, 5 };
        BL4u32_t array_size = BLarray_size2D(BL1u8_t, 640, 480);
        BLarray_alloc(before, array_size);
        BLcommon_randimg(before);
        BLcommon_save_image(BEFORE_BOX_JPG, before, BLimage_save_type_grayscale);
        if (EXIT_SUCCESS != (err = BLfilter2D_box(kbox, before, &after)))
        {
            UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
            break;
        }
        BLcommon_save_image(AFTER_BOX_JPG, after, BLimage_save_type_grayscale);
    } while (0);
    BLSAFEFREE(&before);
    BLSAFEFREE(&after);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

int UTfilter2D_given_kernel()
{
    static const uint8_t sobel_kernel[] = {
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1
    };
    int err = EXIT_SUCCESS;
    pBLarray_t before = NULL, after = NULL;
    do {

    } while (0);
    BLSAFEFREE(&before);
    BLSAFEFREE(&after);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
