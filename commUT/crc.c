#include "comm/BLcrc.h"
#include "base/BLbase.h"

static int crc_pass();
static int crc_error();

int crc()
{
    int err = EXIT_SUCCESS, err_each = EXIT_SUCCESS;
    do {
        err |= (err_each = crc_pass());
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        err |= (err_each = crc_error());
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    return err;
}

static  int crc_pass()
{
    static const uint8_t data8[] = { 0x01, 0x12, 0x14, 0xff, 0x89 };
    int err = EXIT_SUCCESS;
    do {
        BLcrc_t crc;
        BLcrc_init(&crc, CRC_CCITT_LE, 0);
        BLcrc_puts(&crc, data8, ARRAYSIZE(data8));
        uint16_t crc_temp = crc.crc.u16[0];
        if (crc_temp == 0)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLcrc_put16(&crc, &crc_temp);
        if (crc.crc.u16[0])
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int count_bits(uint16_t i)
{
    int icount = 0;
    for (uint16_t imask = 1; imask != 0; imask <<= 1)
    {
        icount += ((imask & i) != 0) ? 1 : 0;
    }
    return icount;
}

static  int crc_error()
{
    static const uint16_t err_bits[] = { 0x0010, 0, 0, 0 };
    uint16_t data16[] = { 0xff1f, 0x0010, 0x1234, 0xabcd };
    int err = EXIT_SUCCESS;
    do {
        BLcrc_t crc;
        BLcrc_init(&crc, CRC_CCITT_LE, 0);
        BLcrc_puts(&crc, (const uint8_t*)data16, sizeof(data16));
        uint16_t crc_temp = crc.crc.u16[0];
        if (crc_temp == 0)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLcrc_put16(&crc, &crc_temp);
        if (crc.crc.u16[0])
        { // check CRC with valid data
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        for (int i = 0; i < ARRAYSIZE(data16); i++)
        { // apply error bits
            data16[i] ^= err_bits[i];
        }
        // check CRC with bit error data
        BLcrc_init(&crc, CRC_CCITT_LE, 0);
        BLcrc_puts(&crc, (const uint8_t*)data16, sizeof(data16));
        BLcrc_put16(&crc, &crc_temp);
        printf("crc = 0x%04x\n", crc.crc.u16[0]);
        int on_bit = count_bits(crc.crc.u16[0]);
        if (on_bit < 7)
        { // CRC check value contains more than or equal to 7 logical one-bits
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}