#include    "study/BLfilter2D.h"
#include    "study/BLmargincopy2D.h"
#include    "study/BLsat.h"
#include    "base/BLintgeo.h"
#include    <errno.h>
#include    <immintrin.h>

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

int BLfilter2D_given_kernel(pcBLarray_t kernel, const BL4i32_t kernel_rect, pcBLarray_t in, pBLarray_t* out)
{
    const size_t kernel_area = (size_t)(kernel->size[1]*kernel->size[2]);
    pBLarray_t in_with_margin = NULL;
    ptrdiff_t *offset_with_margin = (ptrdiff_t*)NULL; // pointer offset for fetching elements in in_with_margin
    const BL4u32_t margin = BLmargins_from_rect(kernel_rect);
    int err = EXIT_SUCCESS;
    do {
        // check kernel->size and kernel_rect consistency
        if ((kernel->size[1] != kernel_rect[2]) || (kernel->size[2] != kernel_rect[3]))
        {
            err = EINVAL;
            break;
        }

        // adding edge margin to in, make in_with_margin
        BLmarginsetup_t margin_setup =
        {
            BLmargintype_extend,
            { kernel_rect[0], kernel_rect[1], kernel_rect[2], kernel_rect[3] },
            (const void*)NULL
        };
        if (EXIT_SUCCESS != (err = BLmargincopy_clone(in, &margin_setup, &in_with_margin)))
        {
            break;
        }
        offset_with_margin = (ptrdiff_t*)malloc(sizeof(ptrdiff_t) * (kernel->size[2]));
        for (uint32_t i = 0; i < kernel->size[2]; i++)
        {
            offset_with_margin[i] = kernel_rect[0] + (kernel_rect[1] + i) * in_with_margin->size[1];
        }

        // initialize out
        BLarray_alloc(*out, in->size);
        // MAC operation over in_with_margin and out
        const BL1r32_t* i_kernel = (const BL1r32_t*)BLarray_begin(kernel);
        BL1r32_t* i_out = (BL1r32_t*)BLarray_begin(*out);
        const BL1r32_t* i_in_with_margin = (const BL1r32_t*)BLarray_at2D(in_with_margin, margin);
        for (uint32_t irow = 0; irow < in->size[2]; irow++)
        {
            for (uint32_t icol = 0; icol < in->size[1]; icol++)
            {
                i_out[icol] = 0.0f;
                for (uint32_t ikernelrow = 0; ikernelrow < kernel->size[2]; ikernelrow++)
                {
                    for (uint32_t ikernelcol = 0; ikernelcol < kernel->size[1]; ikernelcol++)
                    {
                        i_out[icol] += 
                            i_kernel[ikernelcol + ikernelrow * kernel->size[1]] *
                            i_in_with_margin[icol + offset_with_margin[ikernelrow] + ikernelcol];
                    }
                }
            }
            i_out += (*out)->size[1];
            i_in_with_margin += in_with_margin->size[1];
        }
    } while (0);
    BLSAFEFREE(&in_with_margin);
    BLSAFEFREE(&offset_with_margin);
    if (err)
    {
        BLSAFEFREE(out);
    }
    return err;
}

