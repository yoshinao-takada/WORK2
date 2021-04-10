#include    "base/BLbsearch.h"

static int compare(const void* pv0, const void* pv1, const void* param)
{
    int result = 0;
    const int* pvi0 = (const int*)pv0;
    const int* pvi1 = (const int*)pv1;
    if (*pvi0 > *pvi1)
    {
        result = 1;
    }
    else if (*pvi0 < *pvi1)
    {
        result = -1;
    }
    return result;
}

static const int array[] = { -100, -80, -75, -50, -10, 20, 30, 50, 88, 100 };


static int inrange()
{
    int err = EXIT_SUCCESS;
    do {
        int target = -77;
        if (compare(&target, &array[0], NULL) != 1)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (compare(&target, &array[2], NULL) != -1)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BL2u32_t range = { 2, 3 };
        if (BLbsearch_inrange(array, ARRAYSIZE(array), sizeof(array[0]), compare,
            &target, NULL, range))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        target = -75;
        if (!BLbsearch_inrange(array, ARRAYSIZE(array), sizeof(array[0]), compare,
            &target, NULL, range))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        target = -74;
        if (!BLbsearch_inrange(array, ARRAYSIZE(array), sizeof(array[0]), compare,
            &target, NULL, range))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

static int find()
{
    int err = EXIT_SUCCESS;
    do {
        int target = -110;
        BL2u32_t range;
        BLbsearch_find(array, ARRAYSIZE(array), sizeof(int), compare, &target, NULL, range);
        if (range[0] != 0 || range[1] != 0)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        target = 101;
        BLbsearch_find(array, ARRAYSIZE(array), sizeof(int), compare, &target, NULL, range);
        if (range[0] != (ARRAYSIZE(array)-1) || range[1] != ARRAYSIZE(array))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        target = -50;
        BLbsearch_find(array, ARRAYSIZE(array), sizeof(int), compare, &target, NULL, range);
        if (range[0] != 3 || range[1] != 4)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        target = -48;
        BLbsearch_find(array, ARRAYSIZE(array), sizeof(int), compare, &target, NULL, range);
        if (range[0] != 3 || range[1] != 4)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }

    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

static void make_workarray(int** workarray, size_t workarray_size)
{
    int* p = (*workarray = (int*)calloc(workarray_size, sizeof(int)));
    for (int i = 0; i < ARRAYSIZE(array); i++)
    {
        p[i] = array[i];
    }
}

static const int arrayref_after_insert[] = 
{ -100, -80, -75, -50, -10, 20, 30, 45, 50, 88, 100 };
static const int arrayref_after_remove[] =
{ -100, -80, -75, -50, 20, 30, 45, 50, 88, 100 };
static int insert_remove()
{
    size_t array_filled = ARRAYSIZE(array);
    const size_t WORKARRAYSIZE = array_filled + 8;
    int err = EXIT_SUCCESS;
    int* workarray = NULL;
    do {
        make_workarray(&workarray, WORKARRAYSIZE);
        int target = 45;
        BL2u32_t range;
        BLbsearch_find((const void*)workarray, array_filled, sizeof(int), compare,
            &target, NULL, range);
        if (6u != range[0] || 7u != range[1])
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLbsearch_insert((const void*)workarray, array_filled++, sizeof(int),
            &target, range[1]);
        for (int i = 0; i < ARRAYSIZE(arrayref_after_insert); i++)
        {
            if (arrayref_after_insert[i] != workarray[i])
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
        if (err) break;
        target = 100;
        BLbsearch_find((const void*)workarray, array_filled, sizeof(int), compare,
            &target, NULL, range);
        if (range[0] != 10 || range[1] != 11)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        target = -10;
        BLbsearch_find((const void*)workarray, array_filled, sizeof(int), compare,
            &target, NULL, range);
        if (range[0] != 4 || range[1] != 5)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (workarray[range[0]] != target)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        int x;
        err = BLbsearch_remove((void*)workarray, array_filled--, sizeof(int), &x, range[0]);
        if (EXIT_SUCCESS != err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (int i = 0; i < ARRAYSIZE(arrayref_after_remove); i++)
        {
            if (arrayref_after_remove[i] != workarray[i])
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
            }
        }
        if (err) break;
    } while (0);
    BLSAFEFREE(&workarray);
    return err;
}
int bsearch()
{
    int err = EXIT_SUCCESS, err_each = EXIT_SUCCESS;
    do {
        err |= (err_each = inrange());
        err |= (err_each = find());       
        err |= (err_each = insert_remove());
    } while (0);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}