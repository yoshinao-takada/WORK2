#include    "base/BLbase.h"
#include    "comm/BLcrc.h"
int crc();
int packet();

int main()
{
    int err = EXIT_SUCCESS, err_each = EXIT_SUCCESS;
    do {
        err |= (err_each = crc());
        UT_SHOW(stdout, "crc", 0, err_each);
        err |= (err_each = packet());
        UT_SHOW(stdout, "packet", 0, err_each);
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}