#include    "study/BLrandimg.h"


int BLrandimg_grayscale(pBLarray_t img)
{
    srand(0);
    int err = EXIT_SUCCESS;
    pBLarray_t shrinked_img = NULL;
    do {
        BL4u32_t shrinked_size = BLarray_size2D(BL1u8_t, img->size[1]/10 + 1, img->size[2]/10 + 1);
        BLarray_alloc(shrinked_img, shrinked_size);
        BL1u8_t* p = BLarray_begin(shrinked_img);
        uint32_t shrinked_area = BLprod4(shrinked_size);
        do {
            *p++ = (uint8_t)(rand() % 128);
        } while (--shrinked_area);

        BL2u32_t index;
        for (index[1] = 0; index[1] != img->size[2]; index[1]++)
        {
            for (index[0] = 0; index[0] != img->size[1]; index[0]++)
            {
                BL2u32_t shrinked_index = { index[0]/10, index[1]/10 };
                uint8_t val = *(BLarray_at2D(shrinked_img, shrinked_index)) + (uint8_t)(rand() % 128);
                *BLarray_at2D(img, index) = val;
            }
        }
    } while (0);
    BLSAFEFREE(&shrinked_img);
    return err;
}