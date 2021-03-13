#include "math/BLsa.h"
#include "base/BLfile.h"
#include    <math.h>
#define DEFAULT_ARRAY_SIZE  64
#define TIMETICK_CSV    MATH_WORK_DIR "timetick.csv"
#define TDSIGNAL_CSV(ownname)   MATH_WORK_DIR "td-" ownname ".csv"
#define FDSIGNAL_CSV(ownname)   MATH_WORK_DIR "fd-" ownname ".csv"

static int save_realarray_as_csv(const char* filepath, const char* header, pcBLarray1D_t array)
{
    FILE *pf = NULL;
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLfile_open(&pf, filepath, "w")))
        {
            fprintf(stderr, "%s,%d,err=%d,filepath=\"%s\"\n",
                __FUNCTION__, __LINE__, err, filepath);
            break;
        }
        fprintf(pf, "%s\n", header);
        const uint8_t* ptr = BLarray1D_begin(array);
        for (uint16_t i = 0; i != array->size[1]; i++)
        {
            if (array->size[0] == sizeof(BL1r32_t))
            {
                fprintf(pf, "%f\n", *(BL1r32_t*)ptr);
            }
            else if (array->size[0] == sizeof(BL1r64_t))
            {
                fprintf(pf, "%f\n", *(BL1r64_t*)ptr);
            }
            else
            {
                abort();
            }
            ptr += array->size[0];
        }
    } while (0);
    if (pf) { fclose(pf); }
    return err;
}

static int save_signal_as_csv(
    const char* filepath, const char* header,
    pcBLarray1D_t tick, pcBLarray1D_t complex_signal
) {
    int err = EXIT_SUCCESS;
    FILE* pf = NULL;
    do {
        if (EXIT_SUCCESS != (err = BLfile_open(&pf, filepath, "w")))
        {
            fprintf(stderr, "%s,%d,err=%d,filepath=\"%s\"\n",
                __FUNCTION__, __LINE__, err, filepath);
            break;
        }
        fprintf(pf, "%s\n", header);
        const uint8_t* ptr_tick = BLarray1D_begin(tick);
        const uint8_t* ptr_signal = BLarray1D_begin(complex_signal);
        for (uint16_t i = 0; i != tick->size[1]; i++)
        {
            if (tick->size[0] == sizeof(BL1r32_t))
            {
                fprintf(pf, "%f", *(BL1r32_t*)ptr_tick);
            }
            else if (tick->size[0] == sizeof(BL1r64_t))
            {
                fprintf(pf, "%f", *(BL1r64_t*)ptr_tick);
            }
            else
            {
                abort();
            }
            if (complex_signal->size[0] == sizeof(BL1c64_t))
            {
                const BL1c64_t signal = *(const BL1c64_t*)ptr_signal;
                fprintf(pf, ",%f,%f\n", crealf(signal), cimagf(signal));
            }
            else if (complex_signal->size[0] == sizeof(BL1c128_t))
            {
                const BL1c128_t signal = *(const BL1c128_t*)ptr_signal;
                fprintf(pf, ",%f,%f\n", creal(signal), cimag(signal));
            }
            else
            {
                abort();
            }
            ptr_tick += tick->size[0];
            ptr_signal += complex_signal->size[0];
        }
    } while (0);
    if (pf) { fclose(pf); }
    return err;
}

static int sa_new()
{
    int err = EXIT_SUCCESS;
    int err_each = err;
    pBLarray1D_t time_sequence0 = NULL;
    pBLarray1D_t time_sequence1 = NULL;
    do {
        BLsaconf_t conf = { DEFAULT_ARRAY_SIZE, 10.0f, 1.0f/(2 * DEFAULT_ARRAY_SIZE * 10.0f) };
        err_each = BLsa_new(&conf, sizeof(BL1r32_t), BLsainitype_time1r, &time_sequence0);
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE))
        }
        if ((time_sequence0->size[0] != sizeof(BL1r32_t)) ||
            (time_sequence0->size[1] != DEFAULT_ARRAY_SIZE))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLSAFEFREE(&time_sequence0);

        err_each = BLsa_new(&conf, sizeof(BL1r32_t), BLsainitype_time2r, &time_sequence0);
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE))
        }
        if ((time_sequence0->size[0] != sizeof(BL1r32_t)) ||
            (time_sequence0->size[1] != (2*DEFAULT_ARRAY_SIZE)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLSAFEFREE(&time_sequence0);

        err_each = BLsa_new(&conf, sizeof(BL1r32_t), BLsainitype_time1c, &time_sequence0);
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE))
        }
        if ((time_sequence0->size[0] != sizeof(BL1c64_t)) ||
            (time_sequence0->size[1] != DEFAULT_ARRAY_SIZE))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLSAFEFREE(&time_sequence0);

        err_each = BLsa_new(&conf, sizeof(BL1r32_t), BLsainitype_time2c, &time_sequence0);
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE))
        }
        if ((time_sequence0->size[0] != sizeof(BL1c64_t)) ||
            (time_sequence0->size[1] != (2*DEFAULT_ARRAY_SIZE)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLSAFEFREE(&time_sequence0);

        err_each = BLsa_new(&conf, sizeof(BL1r32_t), BLsainitype_time2tick, &time_sequence0);
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if ((time_sequence0->size[0] != sizeof(BL1r32_t)) ||
            (time_sequence0->size[1] != (2*DEFAULT_ARRAY_SIZE)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (EXIT_SUCCESS != save_realarray_as_csv(TIMETICK_CSV, "Time", time_sequence0))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if (EXIT_SUCCESS != (err_each = BLsa_new(&conf, sizeof(BL1r32_t), BLsainitype_time2c, &time_sequence1)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        BLSAFEFREE(&time_sequence0);
        BLSAFEFREE(&time_sequence1);
    } while (0);
    BLSAFEFREE(&time_sequence0);
    BLSAFEFREE(&time_sequence1);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static void sa_fft_setsourcesignal(pcBLsaconf_t conf, pcBLarray1D_t time_tick, pBLarray1D_t sourcesignal)
{
    const BL1r32_t* ptr_time = (const BL1r32_t*)BLarray1D_begin(time_tick);
    BL1c64_t* ptr_sig = (BL1c64_t*)BLarray1D_begin(sourcesignal);
    BL1r32_t w0 = (BL1r32_t)M_PI * 2.0f * conf->df;
    BL1r32_t w1 = 2.0f * w0;
    for (uint16_t i = 0; i != time_tick->size[1]; i++)
    {
        BL1r32_t phi0 = w0 * ptr_time[i];
        BL1r32_t phi1 = w1 * ptr_time[i];
        ptr_sig[i] = CMPLXF(cos(phi0), sin(phi1));
    }
}

static int sa_fft()
{
    static const char* td_header = "t,re,im";
    static const char* fd_header = "f,re,im";
    int err = EXIT_SUCCESS;
    int err_each = err;
    pBLarray1D_t td0 = NULL, td1 = NULL;
    pBLarray1D_t fd = NULL;
    pBLarray1D_t time_tick = NULL, freq_tick = NULL;
    const uint32_t r32size = sizeof(BL1r32_t);
    do {
        BLsaconf_t conf = { DEFAULT_ARRAY_SIZE, 10.0f, 1.0f/(2 * DEFAULT_ARRAY_SIZE * 10.0f) };
        err_each = 
            BLsa_new(&conf, r32size, BLsainitype_time2tick, &time_tick) |
            BLsa_new(&conf, r32size, BLsainitype_freq2tick, &freq_tick) |
            BLsa_new(&conf, r32size, BLsainitype_time2c, &td0) |
            BLsa_new(&conf, r32size, BLsainitype_time2c, &td1) |
            BLsa_new(&conf, r32size, BLsainitype_time2c, &fd);
        if (err_each)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE))
        }
        if (EXIT_SUCCESS != save_realarray_as_csv(TDSIGNAL_CSV("tick"), "Time", time_tick))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        sa_fft_setsourcesignal(&conf, time_tick, td0);
        if (EXIT_SUCCESS != (err_each = save_signal_as_csv(TDSIGNAL_CSV("fft_src"), td_header, time_tick, td0)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = err_each));
        }
        if (EXIT_SUCCESS != (err_each = BLsa_conv(BLsaconvtype_FFT, sizeof(BL1r32_t), td0, fd)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = err_each));
        }
        if (EXIT_SUCCESS != (err_each = save_signal_as_csv(FDSIGNAL_CSV("fft"), fd_header, freq_tick, fd)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = err_each));
        }
    } while (0);
    BLSAFEFREE(&td0);
    BLSAFEFREE(&td1);
    BLSAFEFREE(&fd);
    BLSAFEFREE(&time_tick);
    BLSAFEFREE(&freq_tick);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
int sa()
{
    int err = EXIT_SUCCESS;
    int err_each = err;
    do {
        err |= (err_each = sa_new());
        err |= (err_each = sa_fft());
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

