#ifndef BLINTGEO_H_
#define BLINTGEO_H_
#include    "base/BLbase.h"
#include    "base/BLsv.h"
/*!
\file BLintgeo.h
\brief Geometry of integral number
*/
#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    BLRPx, //!< origin-x
    BLRPy, //!< origin-y
    BLRPw, //!< width
    BLRPh //!< height
} BLrect_param_t;
typedef enum {
    BLMGl, //!< left margin
    BLMGt, //!< top margin
    BLMGr, //!< right margin
    BLMGb //!< bottom margin
} BLmarginid_t;

typedef BL4i32_t    BLrect_t; //!< { x, y, w, h }
typedef BL4u32_t    BLmargins_t; //!< { left, top, right, bottom-margin }

#define BLrect_end(rect) { (rect)[BLRPx] + (rect)[BLRPw], (rect)[BLRPy] + (rect)[BLRPh] };
#define BLmargins_from_rect(rect) { \
    -(rect)[BLRPx], -(rect)[BLRPy], (rect)[BLRPx] + (rect)[BLRPw] - 1, (rect)[BLRPy] + (rect)[BLRPh] -1 }
#define BLrect_area(rect) ((rect)[BLRPw] * (rect)[BLRPh])
#ifdef __cplusplus
}
#endif
#endif /* BLINTGEO_H_ */