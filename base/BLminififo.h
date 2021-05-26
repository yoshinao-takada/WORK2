#ifndef BLMINIFIFO_H_
#define BLMINIFIFO_H_
#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif
typedef struct {
    uint8_t mask;
    uint8_t wrptr;
    uint8_t rdptr;
    uint8_t locker;
} BLminififo_t, *pBLminififo_t;
typedef const BLminififo_t *pcBLminififo_t;

typedef struct {
    BLminififo_t header;
    uint8_t buffer[64];
} BLminififo64_t, *pBLminififo64_t;

#define BLminififo64_inidef     { 0x3f, 0, 0, 0, {0}}

typedef struct {
    BLminififo_t header;
    uint8_t buffer[128];
} BLminififo128_t, *pBLminififo128_t;

#define BLminififo128_inidef     { 0x7f, 0, 0, 0, {0}}

typedef struct {
    BLminififo_t header;
    uint8_t buffer[256];
} BLminififo256_t, *pBLminififo256_t;

#define BLminififo256_inidef     { 0xff, 0, 0, 0, {0}}

typedef enum {
    BLminififo64,
    BLminififo128,
    BLminififo256,
} BLminififotype_t;

/*!
\brief create a new instance of mini-fifo
*/
pBLminififo_t BLminififo_new(BLminififotype_t type);

/*!
\brief put a byte data
\param fifo [in,out] FIFO
\param data [in] 1 byte data
\return 1: success, 0: buffer full 
*/
uint8_t BLminififo_put(pBLminififo_t fifo, uint8_t data);

/*!
\brief get a byte data
\param fifo [in,out] FIFO
\param data [out] 1 byte data
\return 1: success, 0: buffer empty
*/
uint8_t BLminififo_get(pBLminififo_t fifo, uint8_t* data);

/*!
\brief put multile bytes of data
\param fifo [in,out] FIFO
\param data [in] data buffer
\param count [in] byte count to be processed
\return processed byte count
*/
uint8_t BLminififo_puts(pBLminififo_t fifo, const uint8_t*data, uint8_t count);


/*!
\brief get multile bytes of data
\param fifo [in,out] FIFO
\param data [out] data buffer
\param count [in] byte count to be processed
\return processed byte count
*/
uint8_t BLminififo_gets(pBLminififo_t fifo, uint8_t*data, uint8_t count);

/*!
\brief cancel last 1 byte having been put
*/
void BLminififo_cancel(pBLminififo_t fifo);

/*!
\brief simple critical section locking
*/
uint8_t BLminififo_lock(pBLminififo_t fifo);

/*!
\brief simple critical section unlocking
\param fifo [in,out]
*/
#define BLminififo_unlock(fifo) --((fifo)->locker)

/*!
\return true if fifo is empty.
*/
#define BLminififo_isempty(fifo) ((fifo)->wrptr == (fifo)->rdptr)
#ifdef __cplusplus
}
#endif
#endif /* BLMINIFIFO_H_ */