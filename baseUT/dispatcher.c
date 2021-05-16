#include    "base/BLdispatcher.h"
#include    "base/BLbase.h"

static int dispatcher_set_and_clear();
static int dispatcher_dispatch();
static int dispatcher_race_condition();

int dispatcher()
{
    int err = EXIT_SUCCESS, err_each = EXIT_SUCCESS;
    do {
        err |= (err_each = dispatcher_set_and_clear());
        err |= (err_each = dispatcher_dispatch());
        err |= (err_each = dispatcher_race_condition());
    } while (0);
    return err;
}
#pragma region settings
static int contexts[] = { 0, 0, 0, 0 };
static void* handler0(void* pv)
{
    int* pi = (int*)pv;
    (*pi)++;
    return pv;
}

static void* handler1(void* pv)
{
    int* pi = (int*)pv;
    (*pi) += 2;
    return pv;
}

static void* handler2(void* pv)
{
    int* pi = (int*)pv;
    (*pi) += 3;
    return pv;
}

static void* handler3(void* pv)
{
    int* pi = (int*)pv;
    (*pi) += 4;
    return pv;
}

static BLdispatcher_core_t settings[] =
{
    { 1, 1, handler0, &contexts[0] },
    { 2, 2, handler1, &contexts[1] },
    { 3, 3, handler2, &contexts[2] },
    { 4, 4, handler3, &contexts[3] }
};
#pragma endregion settings

static int check_mutex(pthread_mutex_t *mutex)
{
    int err = pthread_mutex_lock(mutex);
    if (err)
    {
        return err;
    }
    err = pthread_mutex_unlock(mutex);
    return err;
}

static int dispatcher_cores_are_equal(pcBLdispatcher_core_t core0, pcBLdispatcher_core_t core1)
{
    int result = (core0->context != core1->context) ? EXIT_FAILURE : EXIT_SUCCESS;
    result |= (core0->handler != core1->handler) ? EXIT_FAILURE : EXIT_SUCCESS;
    result |= (core0->down_counter != core1->down_counter) ? EXIT_FAILURE : EXIT_SUCCESS;
    result |= (core0->down_counter_initial != core1->down_counter_initial) ? EXIT_FAILURE : EXIT_SUCCESS;
    return result;
}

static int is_dispatcher_valid(pBLdispatcher_t dispatcher, pcBLdispatcher_core_t core_ref)
{
    int result = check_mutex(&dispatcher->mutex);
    result |= dispatcher_cores_are_equal(&dispatcher->core, core_ref);
    return result;
}

static int dispatcher_set_and_clear()
{
    int err = EXIT_SUCCESS;
    pBLdispatchers_t dispatchers = NULL;
    size_t item_count = ARRAYSIZE(settings);
    do {
        if (EXIT_SUCCESS != (err = BLdispatchers_new(&dispatchers, item_count)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (size_t i = 0; i < item_count; i++)
        {
            if (EXIT_SUCCESS != (err = BLdispatchers_set(dispatchers, i, &settings[i])))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
        }
        for (size_t i = 0; i < item_count; i++)
        {
            if (EXIT_SUCCESS != (err = is_dispatcher_valid(&dispatchers->dispatchers[i], &settings[i])))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
                break;
            }
        }
    } while (0);
    BLdispatchers_delete(&dispatchers);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

static void show_contexts()
{
    fprintf(stderr, "contexts = { %d, %d, %d, %d }\n",
        contexts[0], contexts[1], contexts[2], contexts[3]);
}

static int dispatcher_dispatch()
{
    int err = EXIT_SUCCESS;
    pBLdispatchers_t dispatchers = NULL;
    size_t item_count = ARRAYSIZE(settings);
    static const int expected_contexts[] = { 8, 8, 6, 8 };
    do {
        if (EXIT_SUCCESS != (err = BLdispatchers_new(&dispatchers, item_count)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (size_t i = 0; i < item_count; i++)
        {
            if (EXIT_SUCCESS != (err = BLdispatchers_set(dispatchers, i, &settings[i])))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
        }
        for (size_t i = 0; i < 8; i++)
        {
            BLdispatchers_dispatch(dispatchers);
        }
        for (size_t i = 0; i < item_count; i++)
        {
            if (expected_contexts[i] != contexts[i])
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
        }
    } while (0);
    BLdispatchers_delete(&dispatchers);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

static int dispatcher_race_condition()
{
    int err = EXIT_SUCCESS;
    pBLdispatchers_t dispatchers = NULL;
    size_t item_count = ARRAYSIZE(settings);
    do {
        if (EXIT_SUCCESS != (err = BLdispatchers_new(&dispatchers, item_count)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (size_t i = 0; i < item_count; i++)
        {
            if (EXIT_SUCCESS != (err = BLdispatchers_set(dispatchers, i, &settings[i])))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
        }
    } while (0);
    BLdispatchers_delete(&dispatchers);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
