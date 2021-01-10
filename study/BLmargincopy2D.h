#ifndef BLMARGINCOPY2D_H_
#define BLMARGINCOPY2D_H_
#include    "base/BLarray.h"
#include    "base/BLintgeo.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    BLmargintype_cyclic,
    BLmargintype_extend,
    BLmargintype_fixed,
    BLmargintype_vertical_cyclic
} BLmargintype_t;

typedef struct {
    BLmargintype_t mt;
    BLrect_t margin_rect;
    const void* fixed_value_ref; //!< fixed value reference
} BLmarginsetup_t, *pBLmarginsetup_t;
typedef const BLmarginsetup_t *pcBLmarginsetup_t;

/*!
\brief create a new array with margin on the four edges and copy the data.
\param map [in] source array
\param margin_setup [in] margin area setup
\param map_with_margin [out] newly created map
\return unix errno compatible number
*/
int BLmargincopy_newarray(pcBLarray_t map, pcBLmarginsetup_t margin_setup, pBLarray_t* map_with_margin);

/*!
\brief create a new array with margins on the four edges without copying data.
\param map [in] source array
\param margin_setup [in] margin area setup
\param map_with_margin [out] newly created map, empty
\return unix errno compatible number
*/
int BLmargincopy_clone(pcBLarray_t map, pcBLmarginsetup_t margin_setup, pBLarray_t* map_with_margin);

/*!
\brief copy to initialized array
\param dst [out] copy destination
\param src [in] copy source
*/
void BLmargincopy_copy(pBLarray_t dst, pcBLmarginsetup_t margin_setup, pcBLarray_t src);
#ifdef __cplusplus
}
#endif
#endif /* BLMARGINCOPY2D_H_ */