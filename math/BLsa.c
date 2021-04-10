#include    "math/BLsa.h"
#include    <assert.h>
#include    <complex.h>
#include    <math.h>
#include    <memory.h>
#include    <mkl.h>
#include    <mkl_dfti.h>

static const uint16_t re_or_cmplx[] =
{
    2, 2, 2, 2,
    1, 1, 1, 1,
    1, 1, 1, 1
};

static const uint16_t is_1_or_2_side[] =
{
    1, 2, 1, 2,
    1, 2, 1, 2,
    1, 2, 1, 2
};
#pragma region array_init_functions

typedef void (*srcfunc_f)(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index);

static void init_cmplx0(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index)
{
    if (realnumsize == 4)
    {
        *(BL1c64_t*)dst = CMPLXF(0.0f, 0.0f);
    }
    else if (realnumsize == 8)
    {
        *(BL1c128_t*)dst = CMPLX(0.0, 0.0);
    }
    else
    {
        assert(0);
    }
}

static void init_real0(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index)
{
    if (realnumsize == 4)
    {
        *(BL1r32_t*)dst = 0.0f;
    }
    else if (realnumsize == 8)
    {
        *(BL1r64_t*)dst = 0.0;
    }
    else
    {
        assert(0);
    }
}

static void init_timetick1(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index)
{
    if (realnumsize == 4)
    {
        *(BL1r32_t*)dst = conf->dt * (BL1r32_t)index;
    }
    else if (realnumsize == 8)
    {
        *(BL1r64_t*)dst = (BL1r64_t)conf->dt * (BL1r64_t)index;
    }
    else
    {
        assert(0);
    }
}

static void init_timetick2(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index)
{
    BL1i32_t indexx = (BL1i32_t)index - (BL1i32_t)conf->point0max;
    if (realnumsize == 4)
    {
        *(BL1r32_t*)dst = conf->dt * (BL1r32_t)indexx;
    }
    else if (realnumsize == 8)
    {
        *(BL1r64_t*)dst = (BL1r64_t)conf->dt * (BL1r64_t)indexx;
    }
    else
    {
        assert(0);
    }
}

static void init_freqtick1(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index)
{
    if (realnumsize == 4)
    {
        *(BL1r32_t*)dst = conf->df * (BL1r32_t)index;
    }
    else if (realnumsize == 8)
    {
        *(BL1r64_t*)dst = (BL1r64_t)conf->df * (BL1r64_t)index;
    }
    else
    {
        assert(0);
    }
}

static void init_freqtick2(uint8_t* dst, pcBLsaconf_t conf, uint32_t realnumsize, uint16_t index)
{
    BL1i32_t indexx = (BL1i32_t)index - (BL1i32_t)conf->point0max;
    if (realnumsize == 4)
    {
        *(BL1r32_t*)dst = conf->df * (BL1r32_t)indexx;
    }
    else if (realnumsize == 8)
    {
        *(BL1r64_t*)dst = (BL1r64_t)conf->df * (BL1r64_t)indexx;
    }
    else
    {
        assert(0);
    }
}

static const srcfunc_f srcfuncs[] =
{
    init_cmplx0, init_cmplx0, init_cmplx0, init_cmplx0,
    init_real0, init_real0, init_real0, init_real0,
    init_timetick1, init_timetick2, init_freqtick1, init_freqtick2
};
#pragma endregion array_init_functions

int BLsa_new
(pcBLsaconf_t conf, uint32_t realnumsize, BLsainitype_t initype, pBLarray1D_t* pparray)
{
    int err = EXIT_SUCCESS;
    const srcfunc_f srcfunc = srcfuncs[initype];
    do {
        BL2u16_t size = 
        { 
            realnumsize * re_or_cmplx[initype],
            conf->point0max * is_1_or_2_side[initype]
        };
        BLarray1D_alloc(*pparray, size);
        uint8_t* ptr = BLarray1D_begin(*pparray);
        for (uint16_t i = 0; i != size[1]; i++)
        {
            srcfunc(ptr, conf, realnumsize, i);
            ptr += size[0];
        }
    } while (0);
    return err;
}

#pragma region conversion_functions
typedef void (*BLconv_f)(uint8_t* dst, const uint8_t* src);

void real_to_complexR32(uint8_t* dst, const uint8_t* src)
{
    *(BL1c64_t*)dst = CMPLXF(*(BL1r32_t*)src, 0.0f);
}
void real_to_complexR64(uint8_t* dst, const uint8_t* src)
{
    *(BL1c128_t*)dst = CMPLX(*(BL1r64_t*)src, 0.0);
}
void complex_to_realR32(uint8_t* dst, const uint8_t* src)
{
    *(BL1r32_t*)dst = crealf(*(BL1c64_t*)src);
}
void complex_to_realR64(uint8_t* dst, const uint8_t* src)
{
    *(BL1r64_t*)dst = creal(*(BL1c128_t*)src);
}
void complex_to_imagR32(uint8_t* dst, const uint8_t* src)
{
    *(BL1r32_t*)dst = cimagf(*(BL1c64_t*)src);
}
void complex_to_imagR64(uint8_t* dst, const uint8_t* src)
{
    *(BL1r64_t*)dst = cimag(*(BL1c128_t*)src);
}
void complex_to_magR32(uint8_t* dst, const uint8_t* src)
{
    BL1r32_t re = crealf(*(const BL1c64_t*)src);
    BL1r32_t im = cimagf(*(const BL1c64_t*)src);
    *(BL1r32_t*)dst = sqrtf(re * re + im * im);
}
void complex_to_magR64(uint8_t* dst, const uint8_t* src)
{
    BL1r64_t re = creal(*(const BL1c128_t*)src);
    BL1r64_t im = cimag(*(const BL1c128_t*)src);
    *(BL1r64_t*)dst = sqrt(re * re + im * im);
}
void complex_to_dBR32(uint8_t* dst, const uint8_t* src)
{
    BL1r32_t re = crealf(*(const BL1c64_t*)src);
    BL1r32_t im = cimagf(*(const BL1c64_t*)src);
    *(BL1r32_t*)dst = 10.0f * log10f(re * re + im * im);
}
void complex_to_dBR64(uint8_t* dst, const uint8_t* src)
{
    BL1r64_t re = creal(*(const BL1c128_t*)src);
    BL1r64_t im = cimag(*(const BL1c128_t*)src);
    *(BL1r64_t*)dst = 10.0 * log10(re * re + im * im);
}
void complex_to_radR32(uint8_t* dst, const uint8_t* src)
{
    *(BL1r32_t*)dst = cargf(*(const BL1c64_t*)src);
}
void complex_to_radR64(uint8_t* dst, const uint8_t* src)
{
    *(BL1r64_t*)dst = carg(*(const BL1c128_t*)src);
}
void complex_to_degR32(uint8_t* dst, const uint8_t* src)
{
    static const float radtodegf = (float)(180.0 / M_PI);
    *(BL1r32_t*)dst = radtodegf * cargf(*(const BL1c64_t*)src);
}
void complex_to_degR64(uint8_t* dst, const uint8_t* src)
{
    static const double radtodeg = (180.0 / M_PI);
    *(BL1r64_t*)dst = radtodeg * carg(*(const BL1c128_t*)src);
}

static const BLconv_f conv_funcsR32[] = 
{
    real_to_complexR32,
    complex_to_realR32,
    complex_to_imagR32,
    complex_to_magR32,
    complex_to_dBR32,
    complex_to_radR32,
    complex_to_degR32,
};

static const BLconv_f conv_funcsR64[] = 
{
    real_to_complexR64,
    complex_to_realR64,
    complex_to_imagR64,
    complex_to_magR64,
    complex_to_dBR64,
    complex_to_radR64,
    complex_to_degR64,
};

static const uint32_t conv_src_stepsR32[] = { 4, 8, 8, 8, 8, 8, 8 };

static const uint32_t conv_src_stepsR64[] = { 8, 16, 16, 16, 16, 16, 16 };

static const uint32_t conv_dst_stepsR32[] = { 8, 4, 4, 4, 4, 4, 4 };

static const uint32_t conv_dst_stepsR64[] = { 16, 8, 8, 8, 8, 8, 8 };

static void swap_half(pcBLarray1D_t in, pBLarray1D_t out)
{
    // first half
    const BL1u8_t* src = BLarray1D_begin(in);
    BL1u8_t* dst = BLarray1D_begin(out);
    size_t copysize = in->size[0] * (in->size[1] >> 1);
    memcpy(dst, src + copysize, copysize);
    memcpy(dst + copysize, src, copysize);
}
static int radunwrapR32(pcBLarray1D_t in, pBLarray1D_t out)
{
    int err = EXIT_SUCCESS;
    do {
        if ((in->size[0] != sizeof(BL1r32_t)) || 
            (out->size[0] != sizeof(BL1r32_t)) ||
            (in->size[1] != out->size[1]))
        {
            err = EINVAL;
        }
        const BL1r32_t* src = (const BL1r32_t*)BLarray1D_begin(in);
        BL1r32_t* dst = (BL1r32_t*)BLarray1D_begin(out);
        *dst = *src;
        BL1r32_t offset = 0.0f;
        for (uint16_t i = 1; i != in->size[1]; i++)
        {
            if ((src[0] < -(BL1r32_t)M_PI_2) && (src[1] >= (BL1r32_t)M_PI_2))
            {
                offset -= (BL1r32_t)(2.0 * M_PI);
            }
            ++src;
            ++dst;
            *dst = *src + offset;
        }
    } while (0);
    return 0;
}
static int radunwrapR64(pcBLarray1D_t in, pBLarray1D_t out)
{
    int err = EXIT_SUCCESS;
    do {
        if ((in->size[0] != sizeof(BL1r64_t)) || 
            (out->size[0] != sizeof(BL1r64_t)) ||
            (in->size[1] != out->size[1]))
        {
            err = EINVAL;
        }
        const BL1r64_t* src = (const BL1r64_t*)BLarray1D_begin(in);
        BL1r64_t* dst = (BL1r64_t*)BLarray1D_begin(out);
        *dst = *src;
        BL1r64_t offset = 0.0;
        for (uint16_t i = 1; i != in->size[1]; i++)
        {
            if ((src[0] < -M_PI_2) && (src[1] >= M_PI_2))
            {
                offset -= (2.0 * M_PI);
            }
            ++src;
            ++dst;
            *dst = *src + offset;
        }
    } while (0);
    return 0;
}
static void fft_checkerr(const char* func_name, MKL_LONG status)
{
    static const struct errclass_caption {
        MKL_LONG errclass;
        const char* caption;
    } errclass_captions[] = {
        { DFTI_NO_ERROR, "NO_ERROR" },
        { DFTI_MEMORY_ERROR, "MEMORY_ERROR" },
        { DFTI_INVALID_CONFIGURATION, "INVALID_CONFIGURATION" },
        { DFTI_INCONSISTENT_CONFIGURATION, "INCONSISTENT_CONFIGURATION" },
        { DFTI_NUMBER_OF_THREADS_ERROR, "NUMBER_OF_THREADS_ERROR" },
        { DFTI_MULTITHREADED_ERROR, "MULTITHREADED_ERROR" },
        { DFTI_BAD_DESCRIPTOR, "BAD_DESCRIPTOR" },
        { DFTI_UNIMPLEMENTED, "UNIMPLEMENTED" },
        { DFTI_MKL_INTERNAL_ERROR, "MKL_INTERNAL_ERROR" },
        { DFTI_1D_LENGTH_EXCEEDS_INT32, "1D_LENGTH_EXCEEDS_INT32" }
    };
    for (int i = 0; i< ARRAYSIZE(errclass_captions); i++)
    {
        if (DftiErrorClass(status, errclass_captions[i].errclass))
        {
            fprintf(stderr, "%s,%d,%s,%s\n", __FUNCTION__, __LINE__, func_name, errclass_captions[i].caption);
        }
    }
}
static int fft(uint32_t realnumsize, pcBLarray1D_t in, pBLarray1D_t out)
{
    int err = EXIT_SUCCESS;
    MKL_LONG mkl_status = 0;
    DFTI_DESCRIPTOR_HANDLE hDescriptor = NULL;
    do {
        enum DFTI_CONFIG_VALUE prec = (realnumsize == sizeof(BL1r32_t)) ? DFTI_SINGLE : DFTI_DOUBLE;
        mkl_status = DftiCreateDescriptor(&hDescriptor, prec, DFTI_COMPLEX, 1, (MKL_LONG)in->size[1]);
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            fft_checkerr("DftiCreateDescriptor", mkl_status);
            err = EFAULT;
            break;
        }
        mkl_status = DftiSetValue(hDescriptor, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            fft_checkerr("DftiSetValue", mkl_status);
            err = EFAULT;
            break;
        }
        mkl_status = DftiCommitDescriptor(hDescriptor);
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            fft_checkerr("DftiCommitDescriptor", mkl_status);
            err = EFAULT;
            break;
        }
        mkl_status = DftiComputeForward(hDescriptor, (void*)BLarray1D_begin(in), (void*)BLarray1D_begin(out));
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            fft_checkerr("DftiComputeForward", mkl_status);
            err = EFAULT;
            break;
        }
        BL1r32_t normalizer = 1.0f / (BL1r32_t)out->size[1];
        BL1c64_t* i_out = (BL1c64_t*)BLarray1D_begin(out);
        for (uint16_t i = 0; i < out->size[1]; i++)
        {
            i_out[i] *= normalizer;
        }
    } while (0);
    return err;
}
static int ifft(uint32_t realnumsize, pcBLarray1D_t in, pBLarray1D_t out)
{
    int err = EXIT_SUCCESS;
    MKL_LONG mkl_status = 0;
    DFTI_DESCRIPTOR_HANDLE hDescriptor = NULL;
    do {
        enum DFTI_CONFIG_VALUE prec = (realnumsize == sizeof(BL1r32_t)) ? DFTI_SINGLE : DFTI_DOUBLE;
        mkl_status = DftiCreateDescriptor(&hDescriptor, prec, DFTI_COMPLEX, 1, (MKL_LONG)in->size[1]);
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            err = EFAULT;
            break;
        }
        mkl_status = DftiSetValue(hDescriptor, DFTI_PLACEMENT, DFTI_NOT_INPLACE);
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            fft_checkerr("DftiSetValue", mkl_status);
            err = EFAULT;
            break;
        }
        mkl_status = DftiCommitDescriptor(hDescriptor);
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            err = EFAULT;
            break;
        }
        mkl_status = DftiComputeBackward(hDescriptor, (void*)BLarray1D_begin(in), (void*)BLarray1D_begin(out));
        if (mkl_status != DFTI_NO_ERROR)
        {
            fprintf(stderr, "%s,%s,%d,mkl_status=%ld\n", __FILE__, __FUNCTION__, __LINE__, mkl_status);
            err = EFAULT;
            break;
        }      
    } while (0);
    return err;
}
#pragma endregion conversion_functions
int BLsa_conv(BLsaconvtype_t convtype, uint32_t realnumsize, pcBLarray1D_t in, pBLarray1D_t out)
{
    int err = EXIT_SUCCESS;
    do {
        if (in->size[1] != out->size[1])
        {
            err = EINVAL;
            fprintf(stderr, "%s,%s,%d,array size mismatch, in-dim=%u, out-dim=%u\n",
                __FILE__, __FUNCTION__, __LINE__, in->size[1], out->size[1]);
            break;
        }
        if (realnumsize != sizeof(BL1r32_t) && realnumsize != sizeof(BL1r64_t))
        {
            err = EINVAL;
            fprintf(stderr, "%s,%s,%d,invalid numsize, numsize=%u\n",
                __FILE__, __FUNCTION__, __LINE__, realnumsize);
            break;
        }
        if (convtype == BLsaconvtype_radunwrap) 
        {
            err = (realnumsize == sizeof(BL1r32_t)) ?  radunwrapR32(in, out) : radunwrapR64(in, out);
        }
        else if (convtype == BLsaconvtype_FFT)
        {
            err = fft(realnumsize, in, out);
        }
        else if (convtype == BLsaconvtype_iFFT)
        {
            err = ifft(realnumsize, in, out);
        }
        else if (convtype == BLsaconvtype_swaphalf)
        {
            swap_half(in, out);
        }
        else
        {
            BL1u8_t* dst = BLarray1D_begin(out);
            const BL1u8_t* src = BLarray1D_begin(in);
            uint32_t src_step, dst_step;
            BLconv_f conv_func = NULL;
            if (realnumsize == sizeof(BL1r32_t))
            {
                src_step = conv_src_stepsR32[convtype];
                dst_step = conv_dst_stepsR32[convtype];
                conv_func = conv_funcsR32[convtype];
            }
            else if (realnumsize == sizeof(BL1r64_t))
            {
                src_step = conv_src_stepsR64[convtype];
                dst_step = conv_dst_stepsR64[convtype];
                conv_func = conv_funcsR64[convtype];
            }
            else
            { // not supported
                abort();
            }
            if ((in->size[0] != src_step) || (out->size[0] != dst_step))
            {
                err = EINVAL;
                fprintf(stderr, "%s,%s,%d,element size mismatch, in-size=%u, out-size=%u\n",
                    __FILE__, __FUNCTION__, __LINE__, in->size[0], out->size[0]);
                break;
            }
            for (uint16_t i = 0; i != in->size[1]; i++)
            {
                conv_func(dst, src);
                dst += dst_step;
                src += src_step;
            }
        }
    } while (0);
    return err;
}
