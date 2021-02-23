#include    "base/BLringbuf.h"
#include    "base/BLbase.h"
#include    <errno.h>
#include    <string.h>

static int available_space();
static int available_data();
static int random_write_read();
static int with_marks();
static int random_write_read_with_marks();

int ringbuf()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = available_space()))
        {
            break;
        }
        if (EXIT_SUCCESS != (err = available_data()))
        {
            break;
        }
        if (EXIT_SUCCESS != (err = random_write_read()))
        {
            break;
        }
        if (EXIT_SUCCESS != (err = with_marks()))
        {

        }
        if (EXIT_SUCCESS != (err = random_write_read_with_marks()))
        {

        }
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int available_space()
{
    int err = EXIT_SUCCESS;
    pBLringbuf_t ringbuf = NULL;
    const uint8_t* src_data = "0123456789ABCDEF";
    do {
        if (EXIT_SUCCESS != (err = BLringbuf_new(7, &ringbuf)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (ringbuf->mask != 0x7f || ringbuf->wrptr != 0 || ringbuf->rdptr != 0)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (BLringbuf_available_space(ringbuf) != 0x7f)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t actual = 0;
        if (BLringbuf_put(ringbuf, 8, src_data, &actual) != EXIT_SUCCESS)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (BLringbuf_available_space(ringbuf) != (0x7f - 8))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&ringbuf);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int available_data()
{
    int err = EXIT_SUCCESS;
    uint8_t src_data[256];
    uint8_t get_buffer[256] = { 0 };
    pBLringbuf_t ringbuf = NULL;
    do {
        if (EXIT_SUCCESS != (err = BLringbuf_new(7, &ringbuf)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (int i = 0; i < sizeof(src_data); i++)
        {
            src_data[i] = (uint8_t)i;
        }
        uint16_t available_space = BLringbuf_available_space(ringbuf);
        uint16_t put_request = available_space >> 1;
        uint16_t actual = 0;
        if ((EXIT_SUCCESS != BLringbuf_put(ringbuf, put_request, src_data, &actual)) ||
            (put_request != actual))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t available_data = BLringbuf_available_data(ringbuf);
        if (available_data != actual)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if ((EXIT_SUCCESS != BLringbuf_get(ringbuf, available_data, get_buffer, &actual)) ||
            (actual != available_data))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (int i = 0; i < actual; i++)
        {
            if (src_data[i] != get_buffer[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (0x7f != (available_space = BLringbuf_available_space(ringbuf)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if ((ENOBUFS != BLringbuf_put(ringbuf, sizeof(src_data), src_data, &actual)) ||
            (available_space != actual))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if ((ENODATA != BLringbuf_get(ringbuf, sizeof(get_buffer), get_buffer, &actual)) ||
            (actual != 0x7f))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (uint16_t i = 0; i < actual; i++)
        {
            if (src_data[i] != get_buffer[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&ringbuf);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static void fill_rand(uint16_t byte_count, uint8_t* buffer)
{
    srand(0);
    for (uint16_t i = 0; i < byte_count; i++)
    {
        buffer[i] = (uint8_t)rand();
    }
}

uint16_t increase_random(uint16_t n, uint16_t limit)
{
    uint16_t inc_value = 0xff & rand();
    uint16_t sum = n + inc_value;
    return __min(sum, limit);
}
static int random_write_read()
{
    uint8_t src_data[4096];
    uint8_t get_buffer[4096];
    int err = EXIT_SUCCESS;
    pBLringbuf_t ringbuf = NULL;
    fill_rand((uint16_t)sizeof(src_data), src_data);
    do {
        BLringbuf_new(7, &ringbuf);
        int end_put = 0, end_get = 0;
        uint16_t i_put = 0, i_get = 0;
        while (!(end_put && end_get))
        {
            uint16_t i_put_next = increase_random(i_put, sizeof(src_data));
            uint16_t i_get_next = increase_random(i_get, sizeof(get_buffer));
            uint16_t put_request = i_put_next - i_put;
            uint16_t get_request = i_get_next - i_get;
            uint16_t actual = 0;
            BLringbuf_put(ringbuf, put_request, src_data + (ptrdiff_t)i_put, &actual);
            i_put += actual;
            end_put = (i_put == sizeof(src_data)) ? 1 : 0;
            BLringbuf_get(ringbuf, get_request, get_buffer + (ptrdiff_t)i_get, &actual);
            i_get += actual;
            end_get = (i_get == sizeof(get_buffer)) ? 1 : 0;
        }
        for (int i = 0; i < sizeof(src_data); i++)
        {
            if (src_data[i] != get_buffer[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
    } while (0);
    BLSAFEFREE(&ringbuf);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int with_marks()
{
    static const char* sources[] = { "abcd", "1234\0", "ABCDE" };
    static const char refstr[] = "1234\0ABCDE";
    int err = EXIT_SUCCESS;
    pBLringbuf_t ringbuf = NULL;
    uint8_t getbuf[64] = {0};
    do {
        if (EXIT_SUCCESS != (err = BLringbuf_new(6, &ringbuf)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t available_space0 = BLringbuf_available_space(ringbuf);
        uint16_t actual = 0;
        if (EXIT_SUCCESS != (err = BLringbuf_put_with_marks(ringbuf, (uint16_t)strlen(sources[0]), sources[0], &actual, BLringbuf_beginmark)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t available_space = BLringbuf_available_space(ringbuf);
        if ((available_space + 2 * 4) != available_space0)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (EXIT_SUCCESS != (err = BLringbuf_put_with_marks(ringbuf, 5, sources[1], &actual, BLringbuf_beginmark)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t available_data = 0;
        if (BLringbuf_beginmark != BLringbuf_available_data_with_marks(ringbuf, &available_data) || 
            (available_data != (uint16_t)strlen(sources[0])))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (EXIT_SUCCESS != (err = BLringbuf_get_with_marks(ringbuf, available_data, getbuf)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (strncmp(sources[0], getbuf, strlen(sources[0])))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (EXIT_SUCCESS != (err = BLringbuf_put_with_marks(ringbuf, (uint16_t)strlen(sources[2]), sources[2], &actual, BLringbuf_nomark)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (BLringbuf_nomark != BLringbuf_available_data_with_marks(ringbuf, &available_data) ||
            (available_data != 10))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (EXIT_SUCCESS != (err = BLringbuf_get_with_marks(ringbuf, available_data, getbuf)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (int i = 0; i != sizeof(refstr); i++)
        {
            if (refstr[i] != getbuf[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&ringbuf);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int random_write_read_with_marks()
{
    int err = EXIT_SUCCESS;
    pBLringbuf_t ringbuf = NULL;
    uint8_t src_data[4096];
    uint8_t get_buffer[4096];
    fill_rand(ARRAYSIZE(src_data), src_data);
    do {
        BLringbuf_new(7, &ringbuf);
        int end_put = 0, end_get = 0;
        uint16_t i_put = 0, i_get = 0;
        while (!(end_put && end_get))
        {
            uint16_t i_put_next = increase_random(i_put, sizeof(src_data));
            BLringbuf_mark_t mark = (BLringbuf_mark_t)(rand() & 1);
            uint16_t put_request = i_put_next - i_put;
            uint16_t actual = 0;
            BLringbuf_put_with_marks(ringbuf, put_request, src_data + (ptrdiff_t)i_put, &actual, mark);
            i_put += actual;
            end_put = (i_put == sizeof(src_data)) ? 1 : 0;
            uint16_t get_request = 0;
            BLringbuf_available_data_with_marks(ringbuf, &get_request);
            BLringbuf_get_with_marks(ringbuf, get_request, get_buffer + (ptrdiff_t)i_get);
            i_get += get_request;
            end_get = (i_get == sizeof(get_buffer)) ? 1 : 0;
        }
        for (int i = 0; i < sizeof(src_data); i++)
        {
            if (src_data[i] != get_buffer[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
    } while (0);
    BLSAFEFREE(&ringbuf);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}