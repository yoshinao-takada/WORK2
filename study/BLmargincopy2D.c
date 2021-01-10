#include    "study/BLmargincopy2D.h"

int BLmargincopy_newarray(pcBLarray_t map, pcBLmarginsetup_t margin_setup, pBLarray_t* map_with_margin)
{
    int err = EXIT_SUCCESS;
    do {
        BL4u32_t new_size = {
            map->size[0], // source map element size
            map->size[1] + // source map Cx
            ((margin_setup->mt == BLmargintype_vertical_cyclic) ? 0 /* no margin */:
             margin_setup->margin_rect[BLRPw] - 1 /* usual margin */),
            map->size[2] + // source map Cy
            margin_setup->margin_rect[BLRPh] - 1 + // usual margin
            ((margin_setup->mt == BLmargintype_vertical_cyclic) ? 2 /* +1 at both of top and bottom */: 0),
            1 }; // always Cz == 1 in 2D array
        BLarray_alloc(*map_with_margin, new_size);
    } while (0);
    return err;
}

int BLmargincopy_clone(pcBLarray_t map, pcBLmarginsetup_t margin_setup, pBLarray_t* map_with_margin)
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLmargincopy_newarray(map, margin_setup, map_with_margin)))
        {
            break;
        }
        BLmargincopy_copy(*map_with_margin, margin_setup, map);
    } while (0);
    return err;
}

static void BLmargincopy_copy_cyclic(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src);
static void BLmargincopy_copy_extend(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src);
static void BLmargincopy_copy_fixed(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src);
static void BLmargincopy_copy_vertical_cyclic(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src);
void BLmargincopy_copy(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src)
{
    switch (margin_setup->mt)
    {
        case BLmargintype_cyclic:
            BLmargincopy_copy_cyclic(dst, margin_setup, src);
            break;
        case BLmargintype_extend:
            BLmargincopy_copy_extend(dst, margin_setup, src);
            break;
        case BLmargintype_fixed:
            BLmargincopy_copy_fixed(dst, margin_setup, src);
            break;
        case BLmargintype_vertical_cyclic:
            BLmargincopy_copy_vertical_cyclic(dst, margin_setup, src);
            break;
        default: break;
    }
}

static void BLmargincopy_copy_cyclic(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src)
{
    BL4u32_t margins = BLmargins_from_rect(margin_setup->margin_rect);
    // copy center area
    {
        BL2u32_t dst_offset = { margins[BLMGl], margins[BLMGt] };
        BL2u32_t src_offset = {0,0};
        BL2u32_t block_size = { src->size[1], src->size[2] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy left margin area
    {
        BL2u32_t dst_offset = { 0, margins[BLMGt] };
        BL2u32_t src_offset = { src->size[1] - margins[BLMGl], 0 };
        BL2u32_t block_size = { margins[BLMGl], src->size[2] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy right margin area
    {
        BL2u32_t dst_offset = { src->size[1] + margins[BLMGl], margins[BLMGt] };
        BL2u32_t src_offset = {0,0};
        BL2u32_t block_size = { margins[BLMGr], src->size[2] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy top margin area
    {
        BL2u32_t dst_offset = {0,0};
        BL2u32_t src_offset = { 0, dst->size[2] - margins[BLMGt] - margins[BLMGb] };
        BL2u32_t block_size = { dst->size[1], margins[BLMGt] };
        BLarray_copy2D(dst, dst_offset, dst, src_offset, block_size);
    }
    // copy bottom margin area
    {
        BL2u32_t dst_offset = { 0, dst->size[2] - margins[BLMGb] };
        BL2u32_t src_offset = { 0, 0 };
        BL2u32_t block_size = { dst->size[1], margins[BLMGb] };
        BLarray_copy2D(dst, dst_offset, dst, src_offset, block_size);
    }
}
static void BLmargincopy_copy_extend(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src)
{
    BL4u32_t margins = BLmargins_from_rect(margin_setup->margin_rect);
    // copy center area
    {
        BL2u32_t dst_offset = { margins[BLMGl], margins[BLMGt] };
        BL2u32_t src_offset = {0,0};
        BL2u32_t block_size = { src->size[1], src->size[2] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy left margin area
    {
        BL2u32_t dst_offset = { 0, margins[BLMGt] };
        BL2u32_t block_size = { margins[BLMGl], 1 };
        BL2u32_t src_edge_point = { 0, 0 };
        for (src_edge_point[1] = 0; src_edge_point[1] != src->size[2]; src_edge_point[1]++)
        {
            BLarray_fill2D(dst, dst_offset, block_size, BLarray_at2D(src, src_edge_point));
            dst_offset[1]++;
        }
    }
    // copy right margin area
    {
        BL2u32_t dst_offset = { src->size[1] + margins[BLMGl], margins[BLMGt] };
        BL2u32_t block_size = { margins[BLMGr], 1 };
        BL2u32_t src_edge_point = { src->size[1] - 1, 0 };
        for (src_edge_point[1] = 0; src_edge_point[1] != src->size[2]; src_edge_point[1]++)
        {
            BLarray_fill2D(dst, dst_offset, block_size, BLarray_at2D(src, src_edge_point));
            dst_offset[1]++;
        }
    }
    // copy top margin area
    {
        BL2u32_t dst_offset = {0,0};
        BL2u32_t src_offset = { 0, margins[BLMGt] };
        BL2u32_t block_size = { dst->size[1], 1 };
        for (dst_offset[1] = 0; dst_offset[1] != margins[BLMGt]; dst_offset[1]++)
        {
            BLarray_copy2D(dst, dst_offset, dst, src_offset, block_size);
        }
    }
    // copy bottom margin area
    {
        BL2u32_t src_offset = { 0, dst->size[2] - margins[BLMGb] - 1 };
        BL2u32_t dst_offset = { 0, 0 };
        BL2u32_t block_size = { dst->size[1], 1 };
        for (dst_offset[1] = src_offset[1]+1; dst_offset[1] != dst->size[2]; dst_offset[1]++)
        {
            BLarray_copy2D(dst, dst_offset, dst, src_offset, block_size);
        }
    }
}
static void BLmargincopy_copy_fixed(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src)
{
    BL4u32_t margins = BLmargins_from_rect(margin_setup->margin_rect);
    // copy center area
    {
        BL2u32_t dst_offset = { margins[BLMGl], margins[BLMGt] };
        BL2u32_t src_offset = {0,0};
        BL2u32_t block_size = { src->size[1], src->size[2] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy left margin area
    {
        BL2u32_t dst_offset = { 0, margins[BLMGt] };
        BL2u32_t block_size = { margins[BLMGl], src->size[2] };
        BLarray_fill2D(dst, dst_offset, block_size, margin_setup->fixed_value_ref);
    }
    // copy right margin area
    {
        BL2u32_t dst_offset = { dst->size[1] - margins[BLMGr], margins[BLMGt] };
        BL2u32_t block_size = { margins[BLMGr], src->size[2] };
        BLarray_fill2D(dst, dst_offset, block_size, margin_setup->fixed_value_ref);
    }
    // copy top margin area
    {
        BL2u32_t dst_offset = { 0, 0 };
        BL2u32_t block_size = { dst->size[1], margins[BLMGt] };
        BLarray_fill2D(dst, dst_offset, block_size, margin_setup->fixed_value_ref);
    }
    // copy bottom margin area
    {
        BL2u32_t dst_offset = { 0, dst->size[2] - margins[BLMGb] };
        BL2u32_t block_size = { dst->size[1], margins[BLMGb] };
        BLarray_fill2D(dst, dst_offset, block_size, margin_setup->fixed_value_ref);
    }
}
static void BLmargincopy_copy_vertical_cyclic(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src)
{
    BLmargins_t margins = BLmargins_from_rect(margin_setup->margin_rect);
    margins[BLMGl] = margins[BLMGr] = 0;
    margins[BLMGt]++; margins[BLMGb]++;
    // copy center area
    {
        BL2u32_t dst_offset = { margins[BLMGl], margins[BLMGt] };
        BL2u32_t src_offset = {0,0};
        BL2u32_t block_size = { src->size[1], src->size[2] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy top margin area
    {
        BL2u32_t dst_offset = {0, 0};
        BL2u32_t src_offset = { 0, src->size[2] - margins[BLMGt] };
        BL2u32_t block_size = { src->size[1], margins[BLMGt] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
    // copy bottom margin area
    {
        BL2u32_t dst_offset = { 0, margins[BLMGt] + src->size[2] };
        BL2u32_t src_offset = { 0, 0 };
        BL2u32_t block_size = { src->size[1], margins[BLMGb] };
        BLarray_copy2D(dst, dst_offset, src, src_offset, block_size);
    }
}
