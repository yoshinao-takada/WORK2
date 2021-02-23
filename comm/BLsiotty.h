#ifndef BLSIOTTY_H_
#define BLSIOTTY_H_
#include    "comm/BLsio.h"

// baudrate identifiers like B9600 are here.
#include    <termios.h>

#ifdef __cplusplus
extern "C" {
#endif

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
typedef const BLtty_setup_t *pcBLtty_setup_t;

#define BLtty_setup_default(name)   { BLBAUD(9600), BLtty_byteformat_N1, name }
#define BLtty_setup_hsdefault(name)   { BLBAUD(115200), BLtty_byteformat_N1, name }

#ifdef __cplusplus
}
#endif
#endif /* BLSIOTTY_H_ */