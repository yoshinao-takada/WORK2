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

typedef int (*BLsio_open_f)(const void* setup_params, void* status, pBLsio_t psio);
typedef int (*BLsio_close_f)(pBLsio_t sio);
typedef int (*BLsio_write_f)(pBLsio_t sio, uint32_t buffer_byte_count, const uint8_t* buffer);
typedef int (*BLsio_read_f)(pBLsio_t sio, uint32_t buffer_byte_count, uint8_t* buffer);

typedef struct {
    BLsio_type_t type;
    BLsio_open_f open;
    BLsio_close_f close;
    BLsio_write_f write;
    BLsio_read_f read;
} BLsio_vtable_t, *pBLsio_vtable_t;
typedef const BLsio_vtable_t *pcBLsio_vtable_t;

pcBLsio_vtable_t BLsio_apis(BLsio_type_t type);

typedef struct {
    int id; // baudrate identifier in linux header,e.g. B9600, B57400
    int baud; // baudrate
    float bit_period; // time period of 1 bit transfer
} BLbaudrate_t, *pBLbaudrate_t;
typedef const BLbaudrate_t *pcBLbaudrate_t;

// this macro defines an instance of BLbaudrate_t.
// e.g. BLBAUD(1200) ==> { B1200, 1200, (1.0f/1200.0f) }
#define BLBAUD(BRNUM) {B ## BRNUM , BRNUM , (1.0f/ BRNUM ## .0f)}
typedef enum {
    BLtty_byteformat_N1, // no parity, 1 stop bit
    BLtty_byteformat_E1, // even parity, 1 stop bit
    BLtty_byteformat_O1, // odd parity, 1 stop bit
    BLtty_byteformat_N2, // no parity, 2 stop bit
    BLtty_byteformat_E2, // even parity, 2 stop bit
    BLtty_byteformat_O2, // odd parity, 2 stop bit
} BLtty_byteformat_t;

#define BLTTY_MAX_NAMELENGTH    32
typedef struct {
    BLbaudrate_t baudrate;
    BLtty_byteformat_t byteformat;
    uint8_t name[BLTTY_MAX_NAMELENGTH];
} BLtty_setup_t, *pBLtty_setup_t;
const BLtty_setup_t *pcBLtty_setup_t;

#define BLtty_setup_default(name)   { BLBAUD(9600), BLtty_byteformat_N1, name }
#define BLtty_setup_hsdefault(name)   { BLBAUD(115200), BLtty_byteformat_N1, name }

#pragma endregion tty_definition
#ifdef __cplusplus
}
#endif
#endif /* BLSIO_H_ */