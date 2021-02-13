#ifndef BLRINGBUF_H_
#define BLRINGBUF_H_
#ifdef __cplusplus
#include    <cstdint>
extern "C" {
#else
#include    <stdint.h>
#endif
typedef struct {
    uint16_t mask;
    uint16_t wrptr;
    uint16_t rdptr;
    uint8_t buffer[0];
} BLringbuf_t, *pBLringbuf_t;
typedef const BLringbuf_t *pcBLringbuf_t;

/*!
\brief create a new ring buffer object
\param count_bits [in] 1..16, effective bit count of mask, wrptr, rdptr.  buffer size
is 2^(count_bits - 1).
\param ppobj [out]
\return errno compatible number
*/
int BLringbuf_new(uint8_t count_bits, pBLringbuf_t* ppobj);

/*!
\brief put byte string
\param obj [in,out] ring buffer object
\param byte_count [in] byte count of data
\param data [in] data to put
\param actual [out] actually put byte count
\return ENOBUFS: Not all data was put because buffer has insufficient space,
    otherwise EXIT_SUCCESS.
*/
int BLringbuf_put(pBLringbuf_t obj, uint16_t byte_count, const uint8_t* data, uint16_t* actual);

/*!
\brief get byte string
\param obj [in,out] ring buffer object
\param byte_count [in] requested byte count
\param data [out] buffer where gotten data is put
\param actual [out] actually gotten byte count
\return ENODATA: Not all data was gotten because buffer has sufficient data,
    otherwise EXIT_SUCCESS.
*/
int BLringbuf_get(pBLringbuf_t obj, uint16_t byte_count, uint8_t* data, uint16_t* actual);

/*!
\brief get current available space
\param obj [in] ring buffer object
\return current availabel space byte count
*/
uint16_t BLringbuf_available_space(pcBLringbuf_t obj);

/*!
\brief get current avalable data byte count
\param obj [in] ring buffer object
\return current availabel data byte count
*/
uint16_t BLringbuf_available_data(pcBLringbuf_t obj);

#ifdef __cplusplus
}
#endif
#endif /* BLRINGBUF_H_ */