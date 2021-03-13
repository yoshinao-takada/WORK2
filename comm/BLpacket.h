#ifndef BLPACKET_H_
#define  BLPACKET_H_
#include    "base/BLbase.h"
#include    "base/BLringbuf.h"
#include    "comm/BLcrc.h"
#ifdef __cplusplus
extern "C" {
#endif

#pragma region basic_packet_operations
#define BLSYNCBYTE   (uint8_t)(0x55)

typedef struct {
    uint8_t ra, sa, sync, pl;
    uint16_t pid, crc;
} BLpacketheader_t, *pBLpacketheader_t;
typedef const BLpacketheader_t *pcBLpacketheader_t;

/*!
\brief initialize a packet header
\param header [out]
\param ra [in] recipient address must != BLSYNCBYTE
\param sa [in] sender address must != BLSYNCBYTE
\param pl [in] payload length including payload CRC
\param pid [in] packet id unique to each combination of ra and sa
*/
void  BLpacketheader_set(
    pBLpacketheader_t header,
    uint8_t ra,
    uint8_t sa,
    uint8_t pl,
    uint16_t pid
);

/*!
\brief check CRC error
\param header [in]
\return EXIT_SUCCESS : no error, EXIT_FAILURE : CRC error
*/
int BLpacketheader_check(pcBLpacketheader_t header);

/*!
\brief check payload CRC error
\param pl [in] payload length
*/
int BLpacketpaylaod_check(uint8_t pl, const uint8_t* data);

/*!
\brief set payload CRC
\param pl [in] payload length
\param data [in,out] buffer holding payload and CRC
*/
void BLpacketpayload_set(uint8_t pl, uint8_t* data);
#pragma endregion basic_packet_operations
#pragma region ringbuf_operation
/*!
\brief check if the oldest 8 byte sequence has a sync mark
\param buf [in] ring buffer
\return EXIT_SUCCESS:success, ENODATA:buffer contents < 8, EINVAL:3rd byte is not sync mark 
*/
int BLringbuf_has_syncmark(pcBLringbuf_t ringbuf);

/*!
\brief get the packet header in the oldest 8 bytes; The 8 bytes are removed only if
the sequence is valid. Otherwise the bytes are reserved.
\param buf [in] ring buffer
\param header [out] packet header which is always modified even if the sequence is invalid.
\return EXIT_SUCCESS:success, ENODATA:buffer contents < 8, EINVAL:3rd byte is not sync mark
    EBADMSG: CRC error in spite that a syncmark is found.
*/
int  BLringbuf_get_packetheader(pBLringbuf_t ringbuf, pBLpacketheader_t header);

/*!
\brief find next syncmark after the 3rd byte
\param ringbuf [in] ring buffer
\return rdptr for the next syncmark if the next syncmark is found. Otherwise UINT16_MAX.
*/
uint16_t BLringbuf_findnextsyncmark(pcBLringbuf_t ringbuf);

/*!
\brief discard invalid sequence until the 2nd syncmark if it exists.
\param ringbuf [in] ring buffer
\return EXIT_SUCCESS or ENODATA
*/
int BLringbuf_discard_invalid_sequence(pBLringbuf_t ringbuf);

/*!
\brief get payload data
\param ringbuf [in] ring buffer, buffer data is reserved if its length is insufficient.
    buffer data is removed if its length is sufficient even though CRC error occures
\param payload_byte_count [in] 
\param data [out] output data buffer
\return EXIT_SUCCESS, EBADMSG: CRC error, ENODATA: available data is insufficient
*/
int BLringbuf_getpayload(pBLringbuf_t ringbuf, uint16_t payload_byte_count, uint8_t* data);
#pragma endregion ringbuf_operation
#pragma region 
#ifdef __cplusplus
}
#endif
#endif /*  BLPACKET_H_ */