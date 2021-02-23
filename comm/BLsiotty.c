#include    <unistd.h>
#include    <termios.h>
#include    <stdio.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <errno.h>
#include    <math.h>
#include    <time.h>
#include    <string.h>
#include    "comm/BLsiotty.h"

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


static int BLtty_setup(pcBLtty_setup_t setup, int fd)
{
    int err = EXIT_SUCCESS;
    do {
        struct termios uart_opt;
        if (EXIT_SUCCESS != tcgetattr(fd, &uart_opt))
        {
            err = errno;
            fprintf(stderr, "%s,%d,errno=%d(0x%04x)\n", __FILE__, __LINE__, err, err);
            break;
        }
        cfsetispeed(&uart_opt, setup->baudrate.id);
        cfsetospeed(&uart_opt, setup->baudrate.id);
        uart_opt.c_cflag |= (CLOCAL | CREAD);
        uart_opt.c_cflag |= ~CRTSCTS; // disable RTS/CTS control
        set_byteformat(&uart_opt, setup->byteformat);
        set_misc_options(&uart_opt);
        if (EXIT_SUCCESS != tcsetattr(fd, TCSANOW, &uart_opt))
        {
            err = errno;
            fprintf(stderr, "%s,%d,errno=%d(0x%04x)\n", __FILE__, __LINE__, err, err);
            break;
        }
    } while (0);
    return err;
}
static int BLtty_open(const void* setup_params, pBLsio_t psio)
{
    pcBLtty_setup_t tty_setup_params = (pcBLtty_setup_t)setup_params;
    int err = EXIT_SUCCESS;
    int fd = -1;
    const char* devicename = (const char*)tty_setup_params->name;
    do {
        if (-1 == (fd = open(devicename, O_RDWR | O_NOCTTY | O_NDELAY)))
        { // open error
            err = errno;
            fprintf(stderr, "%s,%d,errno=%d(0x%04x), %s\n", __FILE__, __LINE__, err, err, devicename);
            break;
        }
        // read() returns immediately even if the read buffer has no characters.
        // see "Serial Programming Guide for POSIX Operating Systems," p.12.
        fcntl(fd, F_SETFL, O_NONBLOCK);
        // setup parameters
        if (EXIT_SUCCESS != (err = BLtty_setup(tty_setup_params, fd)))
        {
            break;
        }
    } while (0);
    if (err)
    { // cleanup
        if (fd != -1)
        { // opened but setup_params caused an error.
            close(fd);
            fd = -1;
        }
    }
    else
    { // serialport was opened and set up well.
        psio->h = (HANDLE)(intptr_t)fd;
        psio->type = BLsio_type_tty;
        psio->status = malloc(sizeof(BLtty_setup_t));
        memcpy(psio->status, setup_params, sizeof(BLtty_setup_t));
    }
    return err;
}

static int BLtty_close(pBLsio_t sio)
{
    int err = EXIT_SUCCESS;
    do {
        close((int)(uintptr_t)sio->h);
        BLSAFEFREE(&sio->status);
    } while (0);
    return err;
}


static void BLtty_estimate_time(pcBLtty_setup_t setup, int byte_count, struct timespec* time)
{
    static const int bits_per_byte[] =
    {
        10, 11, 11, 11, 12, 12
    };
    float total_period = setup->baudrate.bit_period * 
        (float)(bits_per_byte[setup->byteformat] * (int)byte_count);
    float int_part, fract_part;
    fract_part = modff(total_period, &int_part);
    time->tv_sec = (int)int_part;
    time->tv_nsec = (int)(fract_part * 1.0e9);
}

static int BLtty_write(pBLsio_t sio, uint32_t buffer_byte_count, const uint8_t* buffer)
{
    int err = EXIT_SUCCESS;
    pcBLtty_setup_t setup = (pcBLtty_setup_t)sio->status;
    struct timespec sleep_request;
    BLtty_estimate_time(setup, (int)buffer_byte_count, &sleep_request);
    int fd = (int)(intptr_t)sio->h;
    do {
        int not_completed = 1;
        do {
            ssize_t s = write(fd, buffer, (size_t)buffer_byte_count);
            if (s == -1)
            {
                if (EAGAIN != errno)
                { // unexpected error
                    err = errno;
                    not_completed = 0;
                }
                else
                { // sufficient communication buffer is not available
                    nanosleep(&sleep_request, NULL); // wait for an adequate period
                }
            }
            else
            { // write complete
                not_completed = 0;
            }
        } while (not_completed);
    } while (0);
    return err;
}

static int BLtty_read(pBLsio_t sio, uint32_t buffer_byte_count, uint8_t* buffer, uint32_t* actual_read)
{
    int err = EXIT_SUCCESS;
    int fd = (int)(intptr_t)sio->h;
    do {
        ssize_t s = read(fd, buffer, buffer_byte_count);
        if (s == -1)
        {
            if (EAGAIN == (err = errno))
            {
                err = EXIT_SUCCESS;
                *actual_read = 0;
            }
        }
        else
        {
            *actual_read = (uint32_t)s;
        }
    } while (0);
    return err;
}

static const BLsio_apis_t myapis = 
{
    BLsio_type_tty,
    BLtty_open,
    BLtty_close,
    BLtty_write,
    BLtty_read
};

pcBLsio_apis_t BLsiotty_apis() { return &myapis; }