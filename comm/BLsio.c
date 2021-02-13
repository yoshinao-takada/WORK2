#include    <unistd.h>
#include    <termios.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <errno.h>
#include    <math.h>
#include    <time.h>
#include    <string.h>
#include    <unistd.h>
#include    <termios.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <errno.h>
#include    <math.h>
#include    <time.h>
#include    <string.h>
#include    "BLsio.h"

#pragma region tty_definition
static void set_misc_options(struct termios* uart_opt)
{
    // disable canonical input (i.e. raw mode)
    // disable echo normal characters and echo erase characters as BS-SP-BS
    // disable SIGINTR, SIGSUSP, SIGDSUSP, SIGQUIT signals
    uart_opt->c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // dispable X-ON, X-OFF, and any other character sequence flow control
    uart_opt->c_iflag &= ~(IXON | IXOFF | IXANY);
    // disable postprocess outout
    uart_opt->c_oflag &= ~OPOST;
}


static void set_byteformat(struct termios* uart_opt, BLtty_byteformat_t byte_format)
{
    if (byte_format == BLtty_byteformat_N1 || byte_format == BLtty_byteformat_N2)
    {
        uart_opt->c_cflag &= ~PARENB; // disable parity
        uart_opt->c_iflag &= ~(INPCK | ISTRIP);
    }
    else
    {
        uart_opt->c_cflag |= PARENB; // enable parity
        if (byte_format == BLtty_byteformat_E1 || byte_format == BLtty_byteformat_E2)
        {
            uart_opt->c_cflag &= ~PARODD;   
        }
        else
        {
            uart_opt->c_cflag |= PARODD;
        }        
        uart_opt->c_iflag |= (INPCK | ISTRIP);
    }
    uart_opt->c_cflag &= ~CSIZE;
    uart_opt->c_cflag |= CS8;
}


int BLtty_open(const void* setup_params, void* status, pBLsio_t psio)
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

int BLtty_close(pBLsio_t sio)
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

int BLtty_write(pBLsio_t sio, uint32_t buffer_byte_count, const uint8_t* buffer)
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}

int BLtty_read(pBLsio_t sio, uint32_t buffer_byte_count, uint8_t* buffer)
{
    int err = EXIT_SUCCESS;
    do {

    } while (0);
    return err;
}


#pragma endregion tty_definition
