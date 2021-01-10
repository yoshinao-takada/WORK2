#ifndef THREAD_H_
#define THREAD_H_
#include    <time.h>

int thread_sync();

typedef struct {
    struct timespec sleep_request;
    struct timespec sleep_remaining;
    int count;
} CoreProcParam_t, *pCoreProcParam_t;

#endif