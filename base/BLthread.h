#ifndef BLTHREAD_H_
#define BLTHREAD_H_
#include    "base/BLbase.h"
#include    <pthread.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    BLcallback_t procedure;
    void* arg;
    int exit_code; // exit code of the last iteration of procedure execution
} BLthread_core_procedure_t, *pBLthread_core_procedure_t;
typedef const BLthread_core_procedure_t *pcBLthread_core_procedure_t;

// request to thread_runner
typedef enum {
    BLthread_request_none, // continue the thread unchanged
    BLthread_request_last_enter, // exit the thread after the next execution of the core procedure
    BLthread_request_exit_ASAP, // exit the thread as soon as possible
} BLthread_request_t;

typedef struct {
    BLthread_core_procedure_t core;
    pthread_t thread;
    pthread_mutex_t sync_gate_enter;
    pthread_mutex_t sync_gate_exit;
    int exit_code; // thread_runner exit code
    BLthread_request_t request; // request to change thread_runner status
} BLthread_t, *pBLthread_t;
typedef const BLthread_t *pcBLthread_t;

/*!
\brief create a new thread object
\param ppthread [out]
\return errno compatible number
*/
int BLthread_new(pBLthread_t *ppthread, BLcallback_t core_proc, void* core_proc_params);

/*!
\brief delete an object
\param ppthread [in,out]
*/
int BLthread_delete(pBLthread_t *ppthread);

/*!
\brief It allows the core procedure to execute if it is waiting on sync_gate_enter.
\param thread [in,out]
\return errno compatible number
*/
int BLthread_enter_core_proc(pBLthread_t thread, BLthread_request_t request);

/*!
\brief wait for core procedure exiting
\param thread [in,out]
\return errno compatible number
*/
int BLthread_wait_core_proc_exit(pBLthread_t thread);
#ifdef __cplusplus
}
#endif
#endif /* BLTHREAD_H_ */
