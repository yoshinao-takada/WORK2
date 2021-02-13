#include    "base/BLthread.h"
#include    "baseUT/thread.h"
#include    "base/BLts.h"
#include    "base/BLbase.h"

static void* core_proc(void* param)
{
    pCoreProcParam_t param_ = (pCoreProcParam_t)param;
    nanosleep(&param_->sleep_request, &param_->sleep_remaining);
    param_->count++;
    return param;
}


int thread_sync()
{
    static const int iteration = 4;
    int err = EXIT_SUCCESS;
    pBLthread_t thread = (pBLthread_t)NULL;
    CoreProcParam_t param =
    {
        { 0, 400000000 }, // sleep request time = 0.4 sec
        { 0, 0 }
        // count is initialized at the beginning of the for-loop below.
    };

    do {
        if (EXIT_SUCCESS != (err = BLthread_new(&thread, core_proc, (void*)&param)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        for (param.count = 0; param.count < iteration; /* param.count is incremented by core_proc() */)
        {
            struct  timespec ts0, ts1;
            BLts_getnow(&ts0);
            // (iteration - 1) is the last runnable count. At this count, BLthread_request_last_enter notification
            // is sent to thread_runner, requesting thread termination.
            if (EXIT_SUCCESS != (err = BLthread_enter_core_proc(
                thread, param.count == (iteration - 1) ? BLthread_request_last_enter : BLthread_request_none)))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
            if (EXIT_SUCCESS != (err = BLthread_wait_core_proc_exit(thread)))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
            BLts_logelapsedms(stderr, &ts0, "count=%d\n", param.count);
        }
    } while (0);
    err = BLthread_delete(&thread);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

/*
[How to use BLthread]
1. core_proc()
It must be a short sequential function and does not have to consider synchronization.
Synchronization is the role of thread_runner() which is a hidden local function in BLthread.c.
core_proc() does only something short and soon returns.

2. thread_sync()
It controls iteration and synchronization. It lets BLthread framework execute core_proc() repeatedly.
BLthread framework is used as described below.
Step 1: BLthread_new() create a thread executing thread_runner() as a thread.
  The synchronization objects, thread->sync_gate_enter, sync_gate_exit are locked in the initial state.
  thread object is declared as a pointer. The pointer is freed at the end of the program.
  thread_runner() is stop just before calling core_proc() until thread->sync_gate_enter is unlocked.
Step 2, 3 is in a loop.
Step 2: BLthread_enter_core_proc() unlocks thread->sync_gate_enter. The main thread waits on thread->sync_gate_exit
  until the completion of core_proc().
  The request parameter is BLthread_request_last_enter only when the last iteration count. This operation
  notify thread_runner to exit its own loop and terminates the thread.
Step 3: thread_runner() unlocks thread->sync_gate_exit after core_proc() returns. Then the main thread returns
  from BLthread_wait_core_proc_exit().
for-loop exits when param.count == iteration.
Step 4: BLthread_delete() waits for the thread termination by pthread_join() API. And then release resources, i.e.
  two mutexes and thread struct itself.
*/