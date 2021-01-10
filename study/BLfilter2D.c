#include    "study/BLfilter2D.h"
#include    "study/BLmargincopy2D.h"
#include    "study/BLsat.h"
#include    <errno.h>

int BLfilter2D_box(const BL4i32_t kbox, pcBLarray_t in, pBLarray_t* out)
{
    int err = EXIT_SUCCESS;
    pBLarray_t in_with_margin = NULL;
    pBLarray_t sat = NULL;
    do {
        BLmarginsetup_t margin_setup =
        {
            BLmargintype_extend,
            { kbox[0], kbox[1], kbox[2], kbox[3] },
            (const void*)NULL
        };
        if (EXIT_SUCCESS != (err = BLmargincopy_clone(in, &margin_setup, &in_with_margin)))
        {
            break;
        }
        if (EXIT_SUCCESS != (err = BLsat_u32_from_u8(&sat, in_with_margin)))
        {
            break;
        }
        BLarray_alloc(*out, in->size);
        float normalizer = 1.0f / (float)(kbox[2]*kbox[3]);
        BL1u8_t* i_out = (BL1u8_t*)BLarray_begin(*out);
        for (uint32_t iy = 0; iy != in->size[2]; iy++)
        {
            BL4i32_t sumbox = { 0, iy, kbox[2], kbox[3] };
            for (uint32_t ix = 0; ix != in->size[1]; ix++)
            {
                int16_t filtered_value_i16 = (int16_t)(normalizer * BLsat_u32_sum(sat, sumbox));
                i_out[ix] = (uint8_t)__max(0, __min(255, filtered_value_i16));
                sumbox[0]++;
            }
            i_out += in->size[1];
        }
    } while (0);
    BLSAFEFREE(&in_with_margin);
    BLSAFEFREE(&sat);
    return err;
}

int BLfilter2D_given_kernel(pcBLarray_t kernel, pcBLarray_t in, pBLarray_t* out)
{
    int err = EXIT_SUCCESS;
    do {
        // convert uint8_t array to int16_t array

        // convert int16_t array to int32_t array

        // add edge margin to the int32_t array

        // apply filter

        // add 128

        // 
    } while (0);
    return err;
}

int BLfilter2D_cvtu8i32(pcBLarray_t in, pBLarray_t* out)
{
    int err = EXIT_SUCCESS;
    BL4u32_t out_size = BLarray_size2D(int32_t, in->size[1], in->size[2]);
    do {
        BLarray_alloc(*out, out_size);
        if (*out == NULL)
        {
            err = ENOMEM;
            break;
        }
        const BL1u8_t* i_in = BLarray_begin(in);
        BL1i32_t* i_out = (BL1i32_t*)BLarray_begin(*out);
        for (uint32_t iy = 0; iy != in->size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != in->size[1]; ix++)
            {
                i_out[ix] = (int32_t)i_in[ix];
            }
            i_in += in->size[1];
            i_out += in->size[1];
        }
    } while (0);
    return err;
}

int BLfilter2D_addconsti32(int32_t const_num, pcBLarray_t in, pBLarray_t* out)
{
    int err = EXIT_SUCCESS;
    do {
        if (in->size[0] != sizeof(int32_t))
        {
            err = EINVAL;
            break;
        }
        BL4u32_t out_size = BLarray_size2D(int32_t, in->size[1], in->size[2]);
        BLarray_alloc(*out, out_size);
        if (*out == NULL)
        {
            err = ENOMEM;
            break;
        }
        const BL1i32_t* i_in = (const BL1i32_t*)BLarray_begin(in);
        BL1i32_t* i_out = (BL1i32_t*)BLarray_begin(*out);
        for (uint32_t iy = 0; iy != in->size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != in->size[1]; ix++)
            {
                i_out[ix] = i_in[ix] + const_num;
            }
            i_in += in->size[1];
            i_out += in->size[1];
        }
    } while (0);
    return err;
}

int BLfilter2D_cvti32u8(pcBLarray_t in, pBLarray_t* out)
{
    int err = EXIT_SUCCESS;
    do {
        if (in->size[0] != sizeof(int32_t))
        {
            err = EINVAL;
            break;
        }
        BL4u32_t out_size = BLarray_size2D(uint8_t, in->size[1], in->size[2]);
        BLarray_alloc(*out, out_size);
        if (*out == NULL)
        {
            err = ENOMEM;
            break;
        }
        const BL1i32_t* i_in = (const BL1i32_t*)BLarray_begin(in);
        BL1u8_t* i_out = BLarray_begin(*out);
        for (uint32_t iy = 0; iy != in->size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != in->size[1]; ix++)
            {
                i_out[ix] = (uint8_t)i_in[ix];
            }
            i_in += in->size[1];
            i_out += in->size[1];
        }

    } while (0);
    return err;
}
