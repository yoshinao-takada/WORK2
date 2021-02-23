#include    "base/BLbase.h"
#include    "comm/BLsiotty.h"
#include    "comm/BLtoy.h"

int toy()
{
    BLtty_setup_t setup = BLtty_setup_default("/dev/ttyUSB0");
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLtoy_server(&setup)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    return err;
}