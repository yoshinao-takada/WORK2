#ifndef UTMARGINCOPY2D_H_
#define UTMARGINCOPY2D_H_
#include    "study/BLmargincopy2D.h"
#include    "study/BLrandimg.h"
#include    <stdio.h>
#include    <errno.h>
#include    "study/UTcommon.h"
#ifdef __cplusplus
extern "C" {
#endif
int UTmargincopy2D_vertical_cyclic();

int UTmargincopy2D_fixed();

int UTmargincopy2D_extend();

int UTmargincopy2D_cyclic();
#ifdef __cplusplus
}
#endif
#endif /* UTMARGINCOPY2D_H_ */