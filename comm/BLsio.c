#include    "comm/BLsio.h"
#include    "comm/BLsiotty.h"

pcBLsio_apis_t BLsiotty_apis();

pcBLsio_apis_t BLsio_apis(BLsio_type_t type)
{
    switch (type)
    {
        case BLsio_type_tty:
            return BLsiotty_apis();
        default:
            return NULL;
    }
}