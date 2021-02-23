#include    "base/BLbase.h"
#include    "baseUT/ts.h"
#include    "baseUT/thread.h"
#include    "baseUT/UTarray.h"

int ringbuf();
int ser();

int main(int argc, char* argv[])
{
    int err = EXIT_SUCCESS;
    do {
        elapsed(); // elapsed time measurement
        thread_sync(); // thread synchronization
        err = UTcopy2D_4X4_to_2X2();
        err = UTcopy2D_4X4_to_4X4();
        err = ser();
        err = ringbuf();
    } while (0);
    return err;
}