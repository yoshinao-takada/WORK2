#ifndef BLPTRQ_H_
#define BLPTRQ_H_
#include <malloc.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    size_t* element_sizes;
    uint16_t size;
    uint16_t wrpos;
    uint16_t rdpos;
    uint16_t reserved;
    void* elements[0];
} BLptrq_t, *pBLptrq_t;
typedef const BLptrq_t *pcBLptrq_t;

/*!
\brief create a new ptrq.
\param size [in] capacity of the queue
\return pointer to the new object.
*/
pBLptrq_t BLptrq_new(uint16_t size);

/*!
\brief delete object
*/
void BLptrq_delete(pBLptrq_t* ppptrq);

/*!
\brief put a element of any type. copy operation is implemented with memcpy()
*/
int BLptrq_putany(pBLptrq_t q, const void* data, size_t datasize);

/*!
\brief force to put a element of any type
*/
int BLptrq_forceputany(pBLptrq_t q, const void* data, size_t datasize);

/*!
\brief put a null-terminated string of ASCII/UTF-8 encoding
*/
int BLptrq_puts(pBLptrq_t q, const char* string);

/*!
\brief force to put a null-terminated string of ASCII/UTF-8 encoding
*/
int BLptrq_forceputs(pBLptrq_t q, const char* string);


/*!
\brief get a element of any type
*/
void BLptrq_getany(pBLptrq_t q, void* data, size_t datasize);

/*!
\brief peek a data size at the specified position
\param q [in]
\param pos [in] position offset relative from rdpos
\param datasize [out] data size at the specified position
\return errno
*/
int BLptrq_peeksize(pcBLptrq_t q, uint16_t pos, size_t* datasize);

/*!
\brief peek a data block at the specified position
\param q [in]
\param pos [in] position offset relative from rdpos
\param data [out] data output buffer
\param datasize [out] data size at the specified position
*/
void BLptrq_peekany(pcBLptrq_t q, uint16_t pos, void* data, size_t datasize);

/*!
\brief dump all info for debugging
\param q [in]
\param pf [in]
*/
void Blptrq_dumpall(pcBLptrq_t q, FILE* pf);
#ifdef __cplusplus
}
#endif
#endif
