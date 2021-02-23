#ifndef BLSIOTTYAO_H_
#define BLSIOTTYAO_H_
#include    "comm/BLsio.h"
#include    "comm/BLsiotty.h"
#include    "base/BLfsm.h"
#include    "base/BLringbuf.h"
#include    <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif
/*!
\file BLsiottyao.h
\brief active object consisting of an asynchronous TTY reader/writer, a ring buffer,
 and an FSM for binary communication over RS-485 network
*/
typedef struct {
    pthread_t thread;
    pBLringbufex_t q;
    pBLsio_t sio;
    int stop_request;
    BLsio_read_f read_method;
} BLsio_rdthread_t, *pBLsio_rdthread_t;
typedef const BLsio_rdthread_t *pcBLsio_rdthread_t;

typedef struct {
    pthread_t thread;
    pBLringbufex_t q;
    pBLsio_t sio;
    // the write thread wait on it until it is unlocked by an external thread.
    // The external thread unlocks the mutex after the thread puts data in q or
    // sets stop_request.
    pthread_mutex_t thread_locker; 
    int stop_request;
    BLsio_write_f write_method;
} BLsio_wrthread_t, *pBLsio_wrthread_t;
typedef const BLsio_wrthread_t *pcBLsio_wrthread_t;

typedef struct {
    pcBLsio_apis_t api;
    BLfsm_t controller;
    BLsio_t sio;
    BLsio_rdthread_t rdthread;
    BLsio_wrthread_t wrthread;
} BLsioao_t, *pBLsioao_t;
typedef const BLsioao_t *pcBLsioao_t;

/*!
\brief initialize an instance of BLsioao_t.
\param port_setup [in] serialport setup
\param oq_ [in] output queue pointer
\param iq_ [in] input queue pointer
\param obj [out] pointer pointer to the target object
\return unix errno compatible error code
*/
int BLsioao_init(
    pcBLtty_setup_t port_setup,
    pBLringbufex_t oq_,
    pBLringbufex_t iq_,
    pBLsioao_t obj);

/*!
\brief destroy an instance of BLsioao_t.
*/
int BLsioao_destroy(pBLsioao_t obj);

/*!
\brief start a read thread.
*/
int BLsioao_startread(pBLsioao_t obj);

/*!
\brief stop a read thread.
*/
int BLsioao_stopread(pBLsioao_t obj);

/*!
\brief write data async
\param obj [in,out]
\param byte_count [in]
\param data [in]
\return EBUSY: buffer has insufficient space, EXIT_SUCCESS : success
*/
int BLsioao_write(pBLsioao_t obj, uint16_t byte_count, const uint8_t* data);

#ifdef __cplusplus
}
#endif
#endif /* BLSIOTTYAO_H_ */