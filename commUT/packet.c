#include    "comm/BLpacket.h"

static int header_set_check();
static int payload_set_check();
static int ringbuf_has_syncmark();
static int ringbuf_get_packetheader();
static int ringbuf_findnextsyncmark();
static int ringbuf_discard_invalid_sequence();
static int ringbuf_getpayload();

int packet()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = header_set_check()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = payload_set_check()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = ringbuf_has_syncmark()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = ringbuf_get_packetheader()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = ringbuf_findnextsyncmark()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = ringbuf_discard_invalid_sequence()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = ringbuf_getpayload()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int header_set_check()
{
    int err = EXIT_SUCCESS;
    BLpacketheader_t header;
    const uint8_t ra = 0x32;
    const uint8_t sa = 0xff;
    const uint8_t pl = 130;
    const uint16_t packetID = 0x1234;
    do {
        BLpacketheader_set(&header, ra, sa, pl, packetID);
        if (EXIT_SUCCESS != (err = BLpacketheader_check(&header)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        header.ra ^= 0x20;
        if (EXIT_SUCCESS == BLpacketheader_check(&header))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    return err;
}

static int payload_set_check()
{
    #define PAYLOAD_DATA_SIZE   16
    #define PAYLOAD_SIZE        (PAYLOAD_DATA_SIZE + 2)
    int err = EXIT_SUCCESS;
    uint8_t payload[PAYLOAD_SIZE];
    do {
        srand(0);
        BLcrc_t crc;
        BLcrc_init(&crc, CRC_CCITT_LE, 0);
        for (int i = 0; i < PAYLOAD_DATA_SIZE; i++)
        {
            payload[i] = (uint8_t)(rand() & 0xff);
        }
        BLcrc_puts(&crc, payload, PAYLOAD_DATA_SIZE);
        *(uint16_t*)(payload + PAYLOAD_DATA_SIZE) = crc.crc.u16[0];
        crc.crc.u32 = 0;
        BLcrc_puts(&crc, payload, PAYLOAD_SIZE);
        if (0 != crc.crc.u16[0])
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        payload[0] ^= 0x40;
        crc.crc.u32 = 0;
        BLcrc_puts(&crc, payload, PAYLOAD_SIZE);
        if (0 == crc.crc.u16[0])
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
    } while (0);
    return err;
}

static int ringbuf_has_syncmark()
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

static int ringbuf_get_packetheader()
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

static int ringbuf_findnextsyncmark()
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

static int ringbuf_discard_invalid_sequence()
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

static int ringbuf_getpayload()
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

