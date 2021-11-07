#ifndef BLARRAY1D_H_
#define BLARRAY1D_H_
#include    "base/BLbase.h"
#include    "base/BLsv.h"
/*!
\file BLarray1D.h
\brief 1D array for small MCUs
*/
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
    BL2u16_t size; // { element size, element count }
    uint8_t buffer[0];
} BLarray1D_t, *pBLarray1D_t;
typedef const BLarray1D_t *pcBLarray1D_t;

/**
 * @brief create a 1D array object; sample code snippet is shown below
 * pBLarray1D a = NULL;
 * BL2u16_t arraySize = { sizeof(float), 16 };
 * BLarray1D_alloc(a, arraySize); // create a float array, element count = 16
 * ... some code
 * BLSAFEFREE(&a);
 * 
 * @param ptr_var [out] a pointer of the new BLarray1D instance
 * @param _size_ [in] [0]: element size, [1]: element count
 */
#define BLarray1D_alloc(ptr_var, _size_) \
    (ptr_var) = (pBLarray1D_t)malloc(sizeof(BLarray1D_t) + (_size_)[0] * (_size_)[1]); \
    if (ptr_var) { BLcopy2((ptr_var)->size, (_size_)); }

/**
 * @brief create a 1D array with a following extra memory block
 * @param ptr_var [out] a pointer of the new BLarray1D instance
 * @param _size_ [in] [0]: element size, [1]: element count
 * @param _exsize_ [in] byte count of the memory block following the BLarray1D memory block
 */
#define BLarray1D_allocex(ptr_var, _size_, _exsize_) \
    (ptr_var) = (pBLarray1D_t)malloc(sizeof(BLarray1D_t) + (_size_)[0] * (_size_)[1] + (_exsize_)); \
    if (ptr_var) { BLcopy2((ptr_var)->size, (_size_)); }

/**
 * @brief get a pointer to the 1st element. similar to std::vector::begin().
 * @return a uint8_t pointer which sometimes needs to be casted to adequate type. 
 */
#define BLarray1D_begin(ptr_var)    ((ptr_var)->buffer)

/**
 * @brief get a pointer to offset-th element
 * @param ptr_var [in] pointer to an instance of a BLarray1D_t.
 * @param offset [in] index of the target element.
 * @return a uint8_t pointer which sometimes needs to be casted to adequate type. 
 */
#define BLarray1D_at(ptr_var, offset) \
    (BLarray1D_begin(ptr_var) + (offset) * (ptr_var)->size[0])

/**
 * @brief get a pointer to the first memory block just next to the last element. similar to std::vector::end().
 * @param ptr_var [in] pointer to an instance of a BLarray1D_t.
 * @return a uint8_t pointer to the target memroy block. Please take care that it is without const modifier.
 */
#define BLarray1D_end(ptr_var)  (void*)((uint8_t*)BLarray1D_begin(ptr_var) + BLarray1D_totalbytes(ptr_var))

#define BLarray1D_elementsize(ptr_var)  ((ptr_var)->size[0])
#define BLarray1D_elementcount(ptr_var)  ((ptr_var)->size[1])

#define BLarray1D_totalbytes(ptr_var)   ((ptr_var)->size[0] * (ptr_var)->size[1] + sizeof(BLarray1D_t))

#ifdef __cplusplus
}
#endif
#endif /* BLARRAY1D_H_ */