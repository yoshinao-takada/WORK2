#include "math/BLsa.h"
#include "math/BLpoly.h"
#include "base/BLfile.h"
#include    <math.h>
#include    <assert.h>
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
        BL1r32_t phi1 = w1 * ptr_time[i] + 1.0f;
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
    const BL1r32_t freqstep = 10.0f;
    do {
        BLsaconf_t conf = BLsaconf_initbyfreqstep(DEFAULT_ARRAY_SIZE, freqstep);
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
        if (EXIT_SUCCESS != (err_each = BLsa_conv(BLsaconvtype_iFFT, sizeof(BL1r32_t), fd, td1)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = err_each));
        }
        if (EXIT_SUCCESS != (err_each = save_signal_as_csv(TDSIGNAL_CSV("fft_restore"), td_header, time_tick, td1)))
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

static void fill_signal(pcBLarray1D_t DACin, pBLarray1D_t DACout)
{
    assert(DACout->size[1] % DACin->size[1] == 0);
    assert(DACout->size[0] == sizeof(BL1c64_t));
    int ratio = DACout->size[1] / DACin->size[1];
    const uint8_t* i_in = (const uint8_t*)BLarray1D_begin(DACin);
    BL1c64_t* i_out = (BL1c64_t*)BLarray1D_begin(DACout);
    for (uint16_t i = 0; i < DACin->size[1]; i++)
    {
        int jbase = ratio * i;
        for (int j = 0; j < ratio; j++)
        {
            assert((jbase + j) < DACout->size[1]);
            i_out[jbase + j] = CMPLXF(i_in[i], 0.0f);
        }
    }
}

void fill_DACin(pBLarray1D_t DACin)
{
    BL1r32_t T0 = DACin->size[1] / 8.0f, T1 = DACin->size[1] / 13.0f;
    BL1r32_t w0 = 2.0f * M_PI / T0, w1 = 2.0f * M_PI / T1;
    BL1u8_t* i_DACin = (BL1u8_t*)BLarray1D_begin(DACin);
    for (uint16_t i = 0; i != DACin->size[1]; i++)
    {
        i_DACin[i] = (uint8_t)(128.0f + 64.0f * (sinf(w0 * i) + cosf(w1 * i)));
    }
}

static int sa_DAC_sim()
{
    int err = EXIT_SUCCESS;
    pBLarray1D_t DACin = NULL, DACout = NULL, DACout_FD = NULL, DACout_FDView = NULL,
        time_tick = NULL, freq_tick = NULL;
    const uint32_t analysis_sample_DAC_sample_ratio = 8;
    const BL1r32_t 
        DACsps = 1000.0f, // DAC sampling rate = 1 kSps
        signalsps = DACsps * (BL1r32_t)analysis_sample_DAC_sample_ratio; // FFT analysis sampling rate = 8 kSps
    const uint32_t
        DACsamples = 100,
        signalsamples = DACsamples * analysis_sample_DAC_sample_ratio;
    const BL2u16_t DACin_size = { 1, DACsamples };
    const BL2u16_t signal_size = { sizeof(BL1c64_t), DACsamples * analysis_sample_DAC_sample_ratio };
    const BLsaconf_t conf = BLsaconf_initbytimestep(signalsamples / 2, 1.0f/signalsps);
    const uint32_t rnumsize = sizeof(BL1r32_t);
    do {
        err = BLsa_new(&conf, rnumsize, BLsainitype_time2tick, &time_tick) |
            BLsa_new(&conf, rnumsize, BLsainitype_freq2tick, &freq_tick);
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLarray1D_alloc(DACin, DACin_size);
        BLarray1D_alloc(DACout, signal_size);
        BLarray1D_alloc(DACout_FD, signal_size);
        BLarray1D_alloc(DACout_FDView, signal_size);
        if (!DACin || !DACout || !DACout_FD || !DACout_FDView)
        {
           UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        fill_DACin(DACin);
        fill_signal(DACin, DACout);
        if (EXIT_SUCCESS != (err = save_signal_as_csv(TDSIGNAL_CSV("DACout"), "f,re,im", time_tick, DACout)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = BLsa_conv(BLsaconvtype_FFT, rnumsize, DACout, DACout_FD)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = BLsa_conv(BLsaconvtype_swaphalf, rnumsize, DACout_FD, DACout_FDView)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = save_signal_as_csv(FDSIGNAL_CSV("DACout"), "f,re,im", freq_tick, DACout_FDView)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&DACout_FDView);
    BLSAFEFREE(&DACout_FD);
    BLSAFEFREE(&DACout);
    BLSAFEFREE(&DACin);
    BLSAFEFREE(&time_tick);
    BLSAFEFREE(&freq_tick);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

int sa_poly()
{
    int err = EXIT_SUCCESS;
    pBLarray1D_t  poly0 = NULL, poly1 = NULL, poly_prod = NULL;
    do {
        { // number type = BL1r32_t
            const BL1r32_t tol = 1.0e-5f;
            const BL2r32_t poly0src = { 1.0f, 1.0f };
            const BL3r32_t poly1src = { 1.0f, -2.0f, 1.0f };
            BL2u16_t size0 = { sizeof(BL1r32_t), 2 };
            BL2u16_t size1 = { sizeof(BL1r32_t), 3 };
            BL2u16_t size_prod = { size0[0], size0[1] + size1[1] - 1 };
            BLarray1D_alloc(poly0, size0);
            BLarray1D_alloc(poly1, size1);
            BLarray1D_alloc(poly_prod, size_prod);
            BLcopy2((BL1r32_t*)BLarray1D_begin(poly0), poly0src);
            BLcopy3((BL1r32_t*)BLarray1D_begin(poly1), poly1src);
            if (EXIT_SUCCESS != (err = BLpolymultr32(poly0, poly1, poly_prod)))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
            const BL1r32_t x = 1.25f;
            BL1r32_t valref = BLpolyr32(poly0, x) * BLpolyr32(poly1, x);
            BL1r32_t valtest = BLpolyr32(poly_prod, x);
            if (!BL_EQ_F(valref, valtest, tol))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err == EXIT_FAILURE));
            }
            BLSAFEFREE(&poly0);
            BLSAFEFREE(&poly1);
            BLSAFEFREE(&poly_prod);
        }
        { // number type = BL1c64_t
            const BL1r32_t tol = 1.0e-5f;
            const BL2c64_t poly0src = { CMPLXF(1.0f, 0.5f), CMPLXF(-1.0f, 0.5f) };
            const BL3c64_t poly1src = { CMPLXF(1.0f, 0.0f), CMPLXF(-2.0f, 1.0f), CMPLXF(1.0f, 1.0f) };
            BL2u16_t size0 = { sizeof(BL1c64_t), 2 };
            BL2u16_t size1 = { sizeof(BL1c64_t), 3 };
            BL2u16_t size_prod = { size0[0], size0[1] + size1[1] - 1 };
            BLarray1D_alloc(poly0, size0);
            BLarray1D_alloc(poly1, size1);
            BLarray1D_alloc(poly_prod, size_prod);
            BLcopy2((BL1c64_t*)BLarray1D_begin(poly0), poly0src);
            BLcopy3((BL1c64_t*)BLarray1D_begin(poly1), poly1src);
            if (EXIT_SUCCESS != (err = BLpolymultc64(poly0, poly1, poly_prod)))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
            const BL1c64_t x = CMPLXF(1.0f, 0.25f);
            BL1c64_t valref = BLpolyc64(poly0, x) * BLpolyc64(poly1, x);
            BL1c64_t valtest = BLpolyc64(poly_prod, x);
            if (!BL_EQ_CF(valref, valtest, tol))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err == EXIT_FAILURE));
            }
            BLSAFEFREE(&poly0);
            BLSAFEFREE(&poly1);
            BLSAFEFREE(&poly_prod);
        }
        { // number type = BL1r64_t
            const BL1r64_t tol = 1.0e-10;
            const BL2r64_t poly0src = { 1.0, 1.0 };
            const BL3r64_t poly1src = { 1.0, -2.0, 1.0 };
            BL2u16_t size0 = { sizeof(BL1r64_t), 2 };
            BL2u16_t size1 = { sizeof(BL1r64_t), 3 };
            BL2u16_t size_prod = { size0[0], size0[1] + size1[1] - 1 };
            BLarray1D_alloc(poly0, size0);
            BLarray1D_alloc(poly1, size1);
            BLarray1D_alloc(poly_prod, size_prod);
            BLcopy2((BL1r64_t*)BLarray1D_begin(poly0), poly0src);
            BLcopy3((BL1r64_t*)BLarray1D_begin(poly1), poly1src);
            if (EXIT_SUCCESS != (err = BLpolymultr64(poly0, poly1, poly_prod)))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
            const BL1r64_t x = 1.25;
            BL1r64_t valref = BLpolyr64(poly0, x) * BLpolyr64(poly1, x);
            BL1r64_t valtest = BLpolyr64(poly_prod, x);
            if (!BL_EQ_F(valref, valtest, tol))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err == EXIT_FAILURE));
            }
            BLSAFEFREE(&poly0);
            BLSAFEFREE(&poly1);
            BLSAFEFREE(&poly_prod);
        }
        { // number type = BL1c128_t
            const BL1r64_t tol = 1.0e-10;
            const BL2c128_t poly0src = { CMPLX(1.0, 0.5), CMPLX(-1.0, 0.5) };
            const BL3c128_t poly1src = { CMPLX(1.0, 0.0), CMPLX(-2.0, 1.0), CMPLX(1.0, 1.0) };
            BL2u16_t size0 = { sizeof(BL1c128_t), 2 };
            BL2u16_t size1 = { sizeof(BL1c128_t), 3 };
            BL2u16_t size_prod = { size0[0], size0[1] + size1[1] - 1 };
            BLarray1D_alloc(poly0, size0);
            BLarray1D_alloc(poly1, size1);
            BLarray1D_alloc(poly_prod, size_prod);
            BLcopy2((BL1c128_t*)BLarray1D_begin(poly0), poly0src);
            BLcopy3((BL1c128_t*)BLarray1D_begin(poly1), poly1src);
            if (EXIT_SUCCESS != (err = BLpolymultc128(poly0, poly1, poly_prod)))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
            }
            const BL1c128_t x = CMPLX(1.0, 0.25);
            BL1c128_t valref = BLpolyc128(poly0, x) * BLpolyc128(poly1, x);
            BL1c128_t valtest = BLpolyc128(poly_prod, x);
            if (!BL_EQ_CF(valref, valtest, tol))
            {
                UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err == EXIT_FAILURE));
            }
            BLSAFEFREE(&poly0);
            BLSAFEFREE(&poly1);
            BLSAFEFREE(&poly_prod);
        }
    } while (0);
    BLSAFEFREE(&poly0);
    BLSAFEFREE(&poly1);
    BLSAFEFREE(&poly_prod);
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
        err |= (err_each = sa_DAC_sim());
        err |= (err_each = sa_poly());
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

