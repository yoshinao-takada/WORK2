#include    "base/BLbase.h"
#include    "baseUT/ts.h"
#include    "baseUT/thread.h"
#include    "baseUT/UTarray.h"

int ringbuf();
int ser();
int ringbufex();
int heapdebug();
int bsearchUT();
int systick();
int dispatcher();
int settings();
int fifo();
int ptrq();

int main(int argc, char* argv[])
{
    int err = EXIT_SUCCESS;
    do {
        // elapsed(); // elapsed time measurement
        // thread_sync(); // thread synchronization
        // err |= UTcopy2D_4X4_to_2X2();
        // err |= UTcopy2D_4X4_to_4X4();
        // err |= ser();
        // err |= ringbuf();
        // err |= ringbufex();
        // err |= heapdebug();
        // err |= bsearchUT();
        // err |= systick();
        // err |= dispatcher();
        err |= settings();
        err |= fifo();
        err |= ptrq();
    } while (0);
    return err;
}