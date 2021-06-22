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

#define BLarray1D_alloc(ptr_var, _size_) \
    (ptr_var) = (pBLarray1D_t)malloc(sizeof(BLarray1D_t) + (_size_)[0] * (_size_)[1]); \
    if (ptr_var) { BLcopy2((ptr_var)->size, (_size_)); }

#define BLarray1D_allocex(ptr_var, _size_, _exsize_) \
    (ptr_var) = (pBLarray1D_t)malloc(sizeof(BLarray1D_t) + (_size_)[0] * (_size_)[1] + (_exsize_)); \
    if (ptr_var) { BLcopy2((ptr_var)->size, (_size_)); }

#define BLarray1D_begin(ptr_var)    ((ptr_var)->buffer)
#define BLarray1D_at(ptr_var, offset) \
    (BLarray1D_begin(ptr_var) + (offset) * (ptr_var)->size[0])
#define BLarray1D_end(ptr_var)  (void*)((uint8_t*)BLarray1D_begin(ptr_var) + BLarray1D_totalbytes(ptr_var))

#define BLarray1D_elementsize(ptr_var)  ((ptr_var)->size[0])
#define BLarray1D_elementcount(ptr_var)  ((ptr_var)->size[1])

#define BLarray1D_totalbytes(ptr_var)   ((ptr_var)->size[0] * (ptr_var)->size[1] + sizeof(BLarray1D_t))

#ifdef __cplusplus
}
#endif
#endif /* BLARRAY1D_H_ */