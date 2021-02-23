#include    "comm/BLsiottyao.h"
#include    <pthread.h>
#include    <assert.h>

// size of a linear buffer for retrieving contents of wrthread ringbuffer.
// The linear buffer is transfered to write() C-runtime API
#define WRBUF_SIZE  256

/*!
\brief write thread procedure
*/
void* wrthread_proc(void* param)
{
    pBLsio_wrthread_t wrthread = (pBLsio_wrthread_t)param;
    wrthread->stop_request = 0;
    uint8_t wrbuf[WRBUF_SIZE];
    while (wrthread->stop_request == 0)
    {
        pthread_mutex_lock(&wrthread->thread_locker); // wait for external trigger
        uint16_t available_data = 0;
        for (BLringbuf_available_data_with_marks(&wrthread->q->buf, &available_data);
            available_data; )
        {
            pthread_mutex_lock(&wrthread->q->mutex); // lock ringbuffer in q
            BLringbuf_get_with_marks(&wrthread->q->buf, available_data, wrbuf);
            pthread_mutex_unlock(&wrthread->q->mutex); // unlock ringbuffer in q
            wrthread->write_method((void*)&wrthread->sio, available_data, wrbuf);
        }
    }
    wrthread->stop_request = 0;
    return param;
}

static int start_wrthread(pBLsio_wrthread_t wrthread)
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = pthread_mutex_lock(&wrthread->thread_locker)))
        {
            fprintf(stderr, "%s,%d,err=%d(0x%04x)\n", __FUNCTION__, __LINE__, err, err);
            break;
        }
        if (EXIT_SUCCESS != (errno = pthread_create(&wrthread->thread, (const pthread_attr_t*)NULL, wrthread_proc, wrthread)))
        {
            fprintf(stderr, "%s,%d,err=%d(0x%04x)\n", __FUNCTION__, __LINE__, err, err);
            break;
        }
    } while (0);
    return err;
}

static int stop_wrthread(pBLsio_wrthread_t wrthread)
{
    static const struct timespec slp10ms = { 0, 10000000 }; // 10 ms
    int err = EXIT_SUCCESS;
    void* thread_return = NULL;
    do {
        wrthread->stop_request = 1;
        while (wrthread->stop_request)
        {
            pthread_mutex_unlock(&wrthread->thread_locker);
            nanosleep(&slp10ms, (struct timespec*)NULL);
        }
        errno = pthread_join(wrthread->thread, &thread_return);
    } while (0);
    return err;
}

int BLsioao_init(
    pcBLtty_setup_t port_setup,
    pBLringbufex_t oq_,
    pBLringbufex_t iq_,
    pBLsioao_t obj
) {
    int err = EXIT_SUCCESS;
    do {
        obj->api = BLsio_apis(BLsio_type_tty);
        obj->wrthread.q = oq_;
        obj->wrthread.q->buf.rdptr = obj->wrthread.q->buf.wrptr = 0;
        obj->rdthread.q = iq_;
        obj->rdthread.q->buf.rdptr = obj->rdthread.q->buf.wrptr = 0;
        obj->controller.latest_evt = NULL;
        obj->controller.state = NULL;
        obj->controller.context = &obj->sio;
        if (EXIT_SUCCESS != (err = obj->api->open(port_setup, &obj->sio)))
        {
            break;
        }
        obj->wrthread.sio = obj->rdthread.sio = &obj->sio;
        if (EXIT_SUCCESS != (err = pthread_mutex_init(&obj->wrthread.thread_locker, (const pthread_mutexattr_t*)NULL)))
        {
            break;
        }
        obj->wrthread.write_method = obj->api->write;
        obj->rdthread.read_method = obj->api->read;
        err = start_wrthread(&obj->wrthread);
    } while (0);
    return err;
}

int BLsioao_destroy(pBLsioao_t obj)
{
    int err = EXIT_SUCCESS;
    do {
        err = obj->api->close(&obj->sio);
        stop_wrthread(&obj->wrthread);
        pthread_mutex_destroy(&obj->wrthread.thread_locker);
    } while (0);
    return err;
}

int BLsioao_write(pBLsioao_t obj, uint16_t byte_count, const uint8_t* data)
{
    int err = EXIT_SUCCESS;
    pBLsio_wrthread_t wrthread = &obj->wrthread;
    pBLringbufex_t wrq = wrthread->q;
    do {
        if (EXIT_SUCCESS != (err = pthread_mutex_lock(&wrq->mutex)))
        {
            fprintf(stderr, "%s,%d,err=%d(0x%04x)\n", __FUNCTION__, __LINE__, err, err);
            break;
        }
        uint16_t available_space = BLringbuf_available_space(&wrq->buf) >> 1;
        if (available_space >= byte_count)
        {
            uint16_t actual = 0;
            err = BLringbuf_put_with_marks(&wrq->buf, byte_count, data, &actual, BLringbuf_beginmark);
        }
        else
        {
            err = ENOBUFS;
        }
        if (EXIT_SUCCESS != (err = pthread_mutex_unlock(&wrq->mutex)))
        {
            fprintf(stderr, "%s,%d,err=%d(0x%04x)\n", __FUNCTION__, __LINE__, err, err);
            break;
        }
        if (EXIT_SUCCESS != (err = pthread_mutex_unlock(&wrthread->thread_locker)))
        {
            fprintf(stderr, "%s,%d,err=%d(0x%04x)\n", __FUNCTION__, __LINE__, err, err);
            break;
        }
    } while (0);
    return err;
}