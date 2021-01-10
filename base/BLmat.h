#ifndef BLMAT_H_
#define BLMAT_H_
#include    "base/BLbase.h"
#include    "base/BLsv.h"
#ifdef __cplusplus
extern "C" {
#endif

#define BL1(T)    ((T)1)
#define BL0(T)   ((T)0)
#define BL2(T)    ((T)2)

#define BLmatdet2x2(src) ((src)[0] * (src)[3] - (src)[1] * (src)[2])
#define BLmatdet3x3(src) ((src)[0] * ((src)[4] * (src)[8] - (src)[5] * (src)[7]) + \
    (src)[1] * ((src)[5] * (src)[6] - (src)[3] * (src)[8]) + \
    (src)[2] * ((src)[3] * (src)[7] - (src)[4] * (src)[6]))

#define BLmatinv2x2(T,dst,src)    { \
    T _det = BL1(T) / BLmatdet2x2(src); \
    (dst)[0] = (src)[3] * _det; \
    (dst)[3] = (src)[0] * _det; \
    (dst)[1] = -(src)[1] * _det; \
    (dsts)[2] = -(src)[2] * _det; \
}

#define BLmattrans2x2(dst,src) { \
    (dst)[0] = (src)[0]; (dst)[1] = (src)[2]; (dst)[2] = (src)[1]; (dst)[3] = (src)[3]; \
}

#define BLmattrans3x3(dst,src) { \
    (dst)[0] = (src)[0]; (dst)[1] = (src)[3]; (dst)[2] = (src)[6]; \
    (dst)[3] = (src)[1]; (dst)[4] = (src)[4]; (dst)[5] = (src)[7]; \
    (dst)[6] = (src)[2]; (dst)[7] = (src)[5]; (dst)[8] = (src)[8]; \
}

#define BLmattrans4x4(dst,src) { \
    (dst)[0] = (src)[0]; (dst)[1] = (src)[4]; (dst)[2] = (src)[8]; (dst)[3] = (src)[12]; \
    (dst)[4] = (src)[1]; (dst)[5] = (src)[5]; (dst)[6] = (src)[9]; (dst)[7] = (src)[13]; \
    (dst)[8] = (src)[2]; (dst)[9] = (src)[6]; (dst)[10] = (src)[10]; (dst)[11] = (src)[14]; \
    (dst)[12] = (src)[3]; (dst)[13] = (src)[7]; (dst)[14] = (src)[11]; (dst)[15] = (src)[15]; \
}


#define BLmatmul2x2xx2x2(dst,src0,src1) { \
    (dst)[0] = (src0)[0] * (src1)[0] + (src0)[1] * (src1)[2]; \
    (dst)[1] = (src0)[0] * (src1)[1] + (src0)[1] * (src1)[3]; \
    (dst)[2] = (src0)[2] * (src1)[0] + (src0)[3] * (src1)[2]; \
    (dst)[3] = (src0)[2] * (src1)[1] + (src0)[3] * (src1)[3]; \
}

#define BLmatmul2x2xx2x1(dst,src0,src1) { \
    (dst)[0] = (src0)[0] * (src1)[0] + (src0)[1] * (src1)[1]; \
    (dst)[1] = (src0)[2] * (src1)[0] + (src0)[3] * (src1)[1]; \
}

#define BLmatmul3x3xx3x1(dst,src0,src1) { \
    (dst)[0] = (src0)[0] * (src1)[0] + (src0)[1] * (src1)[1] + (src0)[2] * (src1)[2]; \
    (dst)[1] = (src0)[3] * (src1)[0] + (src0)[4] * (src1)[1] + (src0)[5] * (src1)[2]; \
    (dst)[2] = (src0)[6] * (src1)[0] + (src0)[7] * (src1)[1] + (src0)[8] * (src1)[2]; \
}

#define BLmatmul4x4xx4x1(dst,src0,src1) { \
    (dst)[0] = (src0)[0] * (src1)[0] + (src0)[1] * (src1)[1] + (src0)[2] * (src1)[2] + (src0)[3] * (src1)[3]; \
    (dst)[1] = (src0)[4] * (src1)[0] + (src0)[5] * (src1)[1] + (src0)[6] * (src1)[2] + (src0)[7] * (src1)[3]; \
    (dst)[2] = (src0)[8] * (src1)[0] + (src0)[9] * (src1)[1] + (src0)[10] * (src1)[2] + (src0)[11] * (src1)[3]; \
    (dst)[3] = (src0)[12] * (src1)[0] + (src0)[13] * (src1)[1] + (src0)[14] * (src1)[2] + (src0)[15] * (src1)[3]; \
}

#define BLmatmul3x3xx3x3(dst,src0,src1) { \
    (dst)[0] = (src0)[0] * (src1)[0] + (src0)[1] * (src1)[3] + (src0)[2] * (src1)[6]; \
    (dst)[1] = (src0)[0] * (src1)[1] + (src0)[1] * (src1)[4] + (src0)[2] * (src1)[7]; \
    (dst)[2] = (src0)[0] * (src1)[2] + (src0)[1] * (src1)[5] + (src0)[2] * (src1)[8]; \
    (dst)[3] = (src0)[3] * (src1)[0] + (src0)[4] * (src1)[3] + (src0)[5] * (src1)[6]; \
    (dst)[4] = (src0)[3] * (src1)[1] + (src0)[4] * (src1)[4] + (src0)[5] * (src1)[7]; \
    (dst)[5] = (src0)[3] * (src1)[2] + (src0)[4] * (src1)[5] + (src0)[5] * (src1)[8]; \
    (dst)[6] = (src0)[6] * (src1)[0] + (src0)[7] * (src1)[3] + (src0)[8] * (src1)[6]; \
    (dst)[7] = (src0)[6] * (src1)[1] + (src0)[7] * (src1)[4] + (src0)[8] * (src1)[7]; \
    (dst)[8] = (src0)[6] * (src1)[2] + (src0)[7] * (src1)[5] + (src0)[8] * (src1)[8]; \
}

#define BLmatmul4x4xx4x4(dst,src0,src1) { \
    (dst)[0] = (src0)[0] * (src1)[0] + (src0)[1] * (src1)[4] + (src0)[2] * (src1)[8] + (src0)[3] * (src1)[12]; \
    (dst)[1] = (src0)[0] * (src1)[1] + (src0)[1] * (src1)[5] + (src0)[2] * (src1)[9] + (src0)[3] * (src1)[13]; \
    (dst)[2] = (src0)[0] * (src1)[2] + (src0)[1] * (src1)[6] + (src0)[2] * (src1)[10] + (src0)[3] * (src1)[14]; \
    (dst)[3] = (src0)[0] * (src1)[3] + (src0)[1] * (src1)[7] + (src0)[2] * (src1)[11] + (src0)[3] * (src1)[15]; \
    (dst)[4] = (src0)[4] * (src1)[0] + (src0)[5] * (src1)[4] + (src0)[6] * (src1)[8] + (src0)[7] * (src1)[12]; \
    (dst)[5] = (src0)[4] * (src1)[1] + (src0)[5] * (src1)[5] + (src0)[6] * (src1)[9] + (src0)[7] * (src1)[13]; \
    (dst)[6] = (src0)[4] * (src1)[2] + (src0)[5] * (src1)[6] + (src0)[6] * (src1)[10] + (src0)[7] * (src1)[14]; \
    (dst)[7] = (src0)[4] * (src1)[3] + (src0)[5] * (src1)[7] + (src0)[6] * (src1)[11] + (src0)[7] * (src1)[15]; \
    (dst)[8] = (src0)[8] * (src1)[0] + (src0)[9] * (src1)[4] + (src0)[10] * (src1)[8] + (src0)[11] * (src1)[12]; \
    (dst)[9] = (src0)[8] * (src1)[1] + (src0)[9] * (src1)[5] + (src0)[10] * (src1)[9] + (src0)[11] * (src1)[13]; \
    (dst)[10] = (src0)[8] * (src1)[2] + (src0)[9] * (src1)[6] + (src0)[10] * (src1)[10] + (src0)[11] * (src1)[14]; \
    (dst)[11] = (src0)[8] * (src1)[3] + (src0)[9] * (src1)[7] + (src0)[10] * (src1)[11] + (src0)[11] * (src1)[15]; \
    (dst)[12] = (src0)[12] * (src1)[0] + (src0)[13] * (src1)[4] + (src0)[14] * (src1)[8] + (src0)[15] * (src1)[12]; \
    (dst)[13] = (src0)[12] * (src1)[1] + (src0)[13] * (src1)[5] + (src0)[14] * (src1)[9] + (src0)[15] * (src1)[13]; \
    (dst)[14] = (src0)[12] * (src1)[2] + (src0)[13] * (src1)[6] + (src0)[14] * (src1)[10] + (src0)[15] * (src1)[14]; \
    (dst)[15] = (src0)[12] * (src1)[3] + (src0)[13] * (src1)[7] + (src0)[14] * (src1)[11] + (src0)[15] * (src1)[15]; \
}
#ifdef __cplusplus
}
#endif
#endif /*  BLMAT_H_ */
