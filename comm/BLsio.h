#ifndef BLSIO_H_
#define BLSIO_H_
#include    "base/BLbase.h"
/*!
\file BLsio.h
\brief Abstracted serial I/O class. It is assumed to be extended to
RS-485 network, RS-232/-422 1-by-1 communication, I2C/I2S network,
SPI 1-by-1 communication, etc.
*/
#ifdef __cplusplus
extern "C" {
#endif
// device type of BLsio_t
typedef enum {
    BLsio_type_FILE, // file opened by fopen
    BLsio_type_file, // file opened by open
    BLsio_type_tty, // unix style tty
    BLsio_type_atty, // unix aio style tty
    BLsio_type_FT232, // raw FT232 driver
    BLsio_type_I2C, // multidrop I2C master-slave network
    BLsio_type_SPI,
    BLsio_type_I2S,
    BLsio_type_none // do nothing, dummy network
} BLsio_type_t;

typedef struct {
    HANDLE h;
    BLsio_type_t type;
    void* status;
} BLsio_t, *pBLsio_t;
typedef const BLsio_t *pcBLsio_t;

typedef int (*BLsio_open_f)(const void* setup_params, pBLsio_t psio);
typedef int (*BLsio_close_f)(pBLsio_t sio);
typedef int (*BLsio_write_f)(pBLsio_t sio, uint32_t buffer_byte_count, const uint8_t* buffer);
typedef int (*BLsio_read_f)(pBLsio_t sio, uint32_t buffer_byte_count, uint8_t* buffer, uint32_t* actual_read);

/*!
\brief function table structure common to various serial communication configurations
e.g. RS-485, I2C, IrDA, etc.
*/
typedef struct {
    BLsio_type_t type;
    BLsio_open_f open;
    BLsio_close_f close;
    BLsio_write_f write;
    BLsio_read_f read;
} BLsio_apis_t, *pBLsio_apis_t;
typedef const BLsio_apis_t *pcBLsio_apis_t;

/*!
\brief get API function table
*/
pcBLsio_apis_t BLsio_apis(BLsio_type_t type);
#ifdef __cplusplus
}
#endif
#endif /* BLSIO_H_ */