#ifndef BLSA_H_
#define BLSA_H_
/*!
\file BLsa.h
\brief 1-D time-domain and frequency-domain signal analyzer in 1-D arrays
mainly for fourier analysis and statistical analysis.
*/
#include    "base/BLarray1D.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    BL1i32_t point0max; // frequency-domain array element count from 0 to +Fmax
    BL1r32_t df; // frequency step
    BL1r32_t dt; // time step
} BLsaconf_t, *pBLsaconf_t;
typedef const BLsaconf_t *pcBLsaconf_t;

typedef enum {
    // create complex number array filled with zeros
    BLsainitype_time1c, // time-domain one-side
    BLsainitype_time2c, // time-domain two-side
    BLsainitype_freq1c, // frequency-domain one-side
    BLsainitype_freq2c, // frequency-domain two-side
    // create real number array filled with zeros
    BLsainitype_time1r, // time-domain one-side
    BLsainitype_time2r, // time-domain two-side
    BLsainitype_freq1r, // frequency-domain one-side
    BLsainitype_freq2r, // frequency-domain two-side

    // create real number array filled with uniform tick
    BLsainitype_time1tick, // time-domain one-side tick
    BLsainitype_time2tick, // time-domain two-side tick
    BLsainitype_freq1tick, // frequency-domain one-side tick
    BLsainitype_freq2tick, // frequency-domain two-side tick
} BLsainitype_t;

/*!
\brief create a new array-1D object
\param conf [in]
\param realnumsize [in] =2: float16, =4: float, =8: double
\param initype [in]
\param pparray [out]
*/
int BLsa_new(pcBLsaconf_t conf, uint32_t realnumsize, BLsainitype_t initype, pBLarray1D_t* pparray);

typedef enum {
    BLsaconvtype_complex, // real number to complex
    BLsaconvtype_real, // real part
    BLsaconvtype_imag, // imaginary part
    BLsaconvtype_mag, // linear magnitude
    BLsaconvtype_dB, // real number to dB or complex number to dB
    BLsaconvtype_rad, // complex number to radians
    BLsaconvtype_deg, // complex number to degrees
    BLsaconvtype_radunwrap, // unwrap wrapped radian phase plot
    BLsaconvtype_FFT, // FFT
    BLsaconvtype_iFFT, // inverse FFT
    BLsaconvtype_swaphalf, // swap 1st half and 2nd half
} BLsaconvtype_t;
/*!
\brief convert array type
\param convtype [in] conversion type
\param in [in] input array
\param out [out] output array (must be allocated in advance)
*/
int BLsa_conv(BLsaconvtype_t convtype, uint32_t realnumsize, pcBLarray1D_t in, pBLarray1D_t out);
#ifdef __cplusplus
}
#endif
#endif /* BLSA_H_ */