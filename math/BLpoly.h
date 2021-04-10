#ifndef BLPOLY_H_
#define BLPOLY_H_
#include "base/BLarray1D.h"
#ifdef __cplusplus
extern "C" {
#endif
    /*!
    \brief calculate polynomial value
    \param x [in] independent variable
    \param c [in] coefficients of polynomial
    \return polynomial value
    */
    BL1r32_t BLpolyr32(pcBLarray1D_t poly, BL1r32_t x);
    BL1r64_t BLpolyr64(pcBLarray1D_t poly, BL1r64_t x);
    BL1c64_t BLpolyc64(pcBLarray1D_t poly, BL1c64_t x);
    BL1c128_t BLpolyc128(pcBLarray1D_t poly, BL1c128_t x);

    /*!
    \brief multiply two polynomials
    \param poly0 [in] 1st polynomial
    \param poly1 [in] 2nd polynomial
    \param poly_prod [out] product of poly0 and poly1
    \return error code
    */
    int BLpolymultr32(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod);
    int BLpolymultr64(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod);
    int BLpolymultc64(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod);
    int BLpolymultc128(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod);

    /*!
    \brief create a butterworth polynomial
    \param order [in] only [1..8] are supported.
    \param rnumsize [in] gives the real number size, 4: complex float, 8: complex double
    \param pppoly [out] resulted polynomial
    \return error code
    */
    int BLpolybutterworth(uint32_t order, uint32_t rnumsize, pBLarray1D_t* pppoly);

    /*!
    \brief get coefficients of component polynomials of butterworth polynomials
    \param order [in] polynomial order
    \return coefficient array
    i.e. order == 1 : {1.0, 1.0}
        order == 2 : { 1.0, 1.4142, 1.0 }
        order == 3 : { 1.0, 1.0 }, { 1.0, 1.0, 1.0 }
        order == 4 : { 1.0, 0.765, 1.0 }, { 1.0, 1.848, 1.0 }
        order == 5 : { 1.0, 1.0 }, { 1.0, 0.618, 1.0 }, { 1.0, 1.618, 1.0 } ...
    */
    const BL1r32_t* BLpolybutterworthcoeffs(uint32_t order);
#ifdef __cplusplus
}
#endif
#endif /* BLPOLY_H_ */