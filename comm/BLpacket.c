#include    "comm/BLpacket.h"
#include    <assert.h>

#pragma region basic_packet_operations
void  BLpacketheader_set(
    pBLpacketheader_t header,
    uint8_t ra,
    uint8_t sa,
    uint8_t pl,
    uint16_t pid
) {
    assert((ra != BLSYNCBYTE) && (sa != BLSYNCBYTE));
    const uint16_t* p = (const uint16_t*)header;
    BLcrc_t crc;
    header->ra = ra;
    header->sa = sa;
    header->pl = pl;
    header->pid = pid;
    header->sync = BLSYNCBYTE;
    BLcrc_init(&crc, CRC_CCITT_LE, 0);
    BLcrc_put16(&crc, p++);
    BLcrc_put16(&crc, p++);
    BLcrc_put16(&crc, p);
    header->crc = crc.crc.u16[0];
}

int BLpacketheader_check(pcBLpacketheader_t header)
{
    const uint16_t* p = (const uint16_t*)header;
    BLcrc_t crc;
    BLcrc_init(&crc, CRC_CCITT_LE, 0);
    BLcrc_put16(&crc, p++); // ra, sa
    BLcrc_put16(&crc, p++); // sync, pl
    BLcrc_put16(&crc, p++); // pid
    BLcrc_put16(&crc, p); // crc
    return crc.crc.u16[0] ? EXIT_FAILURE : EXIT_SUCCESS;
}

int BLpacketpaylaod_check(uint8_t pl, const uint8_t* data)
{
    BLcrc_t crc;
    BLcrc_init(&crc, CRC_CCITT_LE, 0);
    BLcrc_puts(&crc, data, (uint32_t)pl);
    return crc.crc.u16[0] ? EXIT_FAILURE : EXIT_SUCCESS;
}

void BLpacketpayload_set(uint8_t pl, uint8_t* data)
{
    BLcrc_t crc;
    BLcrc_init(&crc, CRC_CCITT_LE, 0);
    BLcrc_puts(&crc, data, (uint32_t)(pl - 2));
    *(uint16_t*)(data + pl - 2) = crc.crc.u16[0];
}
#pragma endregion basic_packet_operations
#pragma region ringbuf_operation
int BLringbuf_has_syncmark(pcBLringbuf_t ringbuf)
{
    uint16_t available_data = BLringbuf_available_data(ringbuf);
    if (available_data < 8)
    {
        return ENODATA;
    }
    else
    {
        uint16_t syncptr = (uint16_t)((ringbuf->rdptr + 2) & ringbuf->mask);
        return (ringbuf->buffer[syncptr] == BLSYNCBYTE) ? EXIT_SUCCESS : EINVAL;
    }
}

int BLringbuf_getpacketheader(pBLringbuf_t ringbuf, pBLpacketheader_t header)
{
    int err = BLringbuf_has_syncmark(ringbuf);
    if (err) return err;
    uint8_t *dst = (uint8_t*)header;
    for (uint16_t i = 0; i < sizeof(BLpacketheader_t); i++)
    {
        uint16_t srcptr = (ringbuf->rdptr + i) & ringbuf->mask;
        dst[i] = ringbuf->buffer[srcptr];
    }
    if (BLpacketheader_check(header) == EXIT_SUCCESS)
    {
        ringbuf->rdptr = (ringbuf->rdptr + sizeof(BLpacketheader_t)) & ringbuf->mask;
    }
    else
    {
        err = EBADMSG;
    }
    return err;
}

uint16_t BLringbuf_findnextsyncmark(pcBLringbuf_t ringbuf)
{
    for (uint16_t ptr = (ringbuf->rdptr + 3) & ringbuf->mask; ptr != ringbuf->wrptr;
        ptr = (ptr + 1) & ringbuf->mask)
    {
        if (ringbuf->buffer[ptr] == BLSYNCBYTE)
        {
            return ptr;
        }
    }
    return UINT16_MAX;
}

int BLringbuf_discard_invalid_sequence(pBLringbuf_t ringbuf)
{
    uint16_t nextsyncmark = BLringbuf_findnextsyncmark(ringbuf);
    if (nextsyncmark == UINT16_MAX)
    {
        return ENODATA;
    }
    ringbuf->rdptr = (nextsyncmark - 2) & ringbuf->mask;
    return EXIT_SUCCESS;
}

int BLringbuf_getpayload(pBLringbuf_t ringbuf, uint16_t payload_byte_count, uint8_t* data)
{
    uint16_t available_data_bytes = BLringbuf_available_data(ringbuf);
    if (available_data_bytes < payload_byte_count)
    {
        return ENODATA;
    }
    BLringbuf_get(ringbuf, payload_byte_count, data, &available_data_bytes);
    BLcrc_t crc;
    BLcrc_init(&crc, CRC_CCITT_LE, 0);
    BLcrc_puts(&crc, data, (uint32_t)payload_byte_count);
    return crc.crc.u16[0] ? EBADMSG : EXIT_SUCCESS;
}
#pragma endregion ringbuf_operation
