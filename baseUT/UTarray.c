#include    "baseUT/UTarray.h"
#include    <errno.h>

static int AreEqualElements(const BL2u32_t* x0, const BL2u32_t* x1)
{
    return (((*x0)[0] == (*x1)[0]) && ((*x0)[1] == (*x1)[1])) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int AreEqual(const BL2u32_t* x0, const BL2u32_t* x1, const BL2u32_t size)
{
    int are_equal = EXIT_SUCCESS;
    uint32_t area = size[0] * size[1];
    do {
        if (EXIT_SUCCESS != (are_equal = AreEqualElements(x0, x1)))
        {
            break;
        }
        x0++;
        x1++;
    } while (--area);
    return are_equal;
}

int UTAreEqual()
{
    int err = EXIT_SUCCESS;
    BL2u32_t size = {4,4};
    const BL2u32_t x0[] = REF4X4_0;
    BL2u32_t x1[] = REF4X4_0;
    do {
        int result = AreEqual(x0, x1, size);
        UT_SHOW(stderr, __FUNCTION__, __LINE__, result);
        IF_TRUE_SETERRBREAK(result == EXIT_FAILURE, err, EXIT_FAILURE);
        BLcopy2(x1[4], x1[5]);
        result = AreEqual(x0, x1, size);
        UT_SHOW(stderr, __FUNCTION__, __LINE__, result);
        IF_TRUE_SETERRBREAK(result == EXIT_SUCCESS, err, EXIT_FAILURE);
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

int UTcopy2D_4X4_to_2X2()
{
    static const BL2u32_t src4X4_0Raw[] = SRC4X4_0;
    int err = EXIT_SUCCESS;
    pBLarray_t src4X4_0 = NULL, src4X4_1 = NULL;
    pBLarray_t test2X2 = NULL;
    do {
        // memory allocation
        BL4u32_t size4X4 = BLarray_size2D(BL2u32_t, 4, 4);
        BL4u32_t size2X2 = BLarray_size2D(BL2u32_t, 2, 2);
        BLarray_alloc(src4X4_0, size4X4);
        BLarray_alloc(test2X2, size2X2);
        if ((!src4X4_0) || (!test2X2))
        {
            err = ENOMEM;
            UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
            break;
        }
        // init source arrays
        memcpy(BLarray_begin(src4X4_0), src4X4_0Raw, BLprod4(src4X4_0->size));
        { // test1: copy 2x2 block from src4X4_0 to test2X2.
            BL2u32_t src_offset = { 2, 1 };
            BL2u32_t dst_offset = { 0, 0 };
            BL2u32_t block_size = { 2, 2 };
            BLarray_copy2D(test2X2, dst_offset, src4X4_0, src_offset, block_size);
            const BL2u32_t ref[] = REF2X2_0;
            err = AreEqual(ref, (const BL2u32_t*)BLarray_begin(test2X2), block_size);
            UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
            IF_TRUE_BREAK(err);
        }
        { // test1: copy 2x2 block from src4X4_0 to test2X2.
            BL2u32_t src_offset = { 0, 2 };
            BL2u32_t dst_offset = { 0, 0 };
            BL2u32_t block_size = { 2, 2 };
            BLarray_copy2D(test2X2, dst_offset, src4X4_0, src_offset, block_size);
            const BL2u32_t ref[] = REF2X2_1;
            err = AreEqual(ref, (const BL2u32_t*)BLarray_begin(test2X2), block_size);
            UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
            IF_TRUE_BREAK(err);
        }
    } while (0);
    // releasing memory allocated to arrays
    BLSAFEFREE(&test2X2);
    BLSAFEFREE(&src4X4_0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
int UTcopy2D_4X4_to_4X4()
{
    static const BL2u32_t src4X4_0Raw[] = SRC4X4_0;
    static const BL2u32_t src4X4_1Raw[] = SRC4X4_1;
    pBLarray_t src4X4_0 = NULL, src4X4_1 = NULL, test4X4 = NULL;
    int err = EXIT_SUCCESS;
    do {
        // memory allocation
        BL4u32_t size4X4 = BLarray_size2D(BL2u32_t, 4, 4);
        BL4u32_t size2X2 = BLarray_size2D(BL2u32_t, 2, 2);
        BLarray_alloc(src4X4_0, size4X4);
        BLarray_alloc(src4X4_1, size4X4);
        BLarray_alloc(test4X4, size4X4);
        if ((!src4X4_0) || (!src4X4_1) || (!test4X4))
        {
            err = ENOMEM;
            UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
            break;
        }
        // init suorce arrays
        memcpy(BLarray_begin(src4X4_0), src4X4_0Raw, BLprod4(src4X4_0->size));
        memcpy(BLarray_begin(src4X4_1), src4X4_1Raw, BLprod4(src4X4_1->size));
        // copy src4X4_0 and src4X4_1 to test4X4
        {
            BL2u32_t dst_offset = { 0, 0 };
            BL2u32_t src_offset = { 0, 0 };
            BL2u32_t block_size = { 4, 4 };
            BLarray_copy2D(test4X4, dst_offset, src4X4_0, src_offset, block_size);
        }
        {
            BL2u32_t dst_offset = { 2, 0 };
            BL2u32_t src_offset = { 0, 2 };
            BL2u32_t block_size = { 2, 2 };
            BLarray_copy2D(test4X4, dst_offset, src4X4_1, src_offset, block_size);
        }
        // check copy results
        {
            BL2u32_t block_size = { 4, 4 };
            const BL2u32_t ref[] = REF4X4_1;
            err = AreEqual(ref, (const BL2u32_t*)BLarray_begin(test4X4), block_size);
            if (err != EXIT_SUCCESS)
            {
                UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
                break;
            }
        }
    } while (0);
    // releasing memory allocated to arrays
    BLSAFEFREE(&src4X4_0);
    BLSAFEFREE(&src4X4_1);
    BLSAFEFREE(&test4X4);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
