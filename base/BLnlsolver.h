#ifndef BLSOLVER_H_
#define BLSOLVER_H_
#ifdef __cplusplus
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
extern "C" {
#else
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#endif
// refer to
// Jan A. Snyman and Daniel N. Wilke ",Practical Mathematical Optimization,
//  Basic Optimization Theory and Gradient-Based Algorithms"
// p.87
#define FILL_FLOATS(a,val,count) for (int i = 0; i < count; i++) { a[i] = val; }


/**
 * @brief set array with constant initializer; sample code snippet is shown below
 * float* a = (float*)calloc(3, sizeof(float));
 * SET_FLOATS(a, {1.0f,2.0f,3.0f});
 * ... some code
 * free((void*)a);
 * @aram a [in,out] array variable or pointer
 * @param aIni [in] constant initializer like { 1.0f, 2.0f, 3.0f }
 */
#define SET_FLOATS(a,aIni) { \
    float aIni_[] = aIni; \
    for (int i = 0; i < ARRAYSIZE(aIni); i++) { a[i] = aIni_[i]; } \
}
/**
 * @brief objective function under optimization
 * @param cx [in] array size of x
 * @param x [in] variables
 * @param cp [in] array size of params
 * @param params [in] fixed parameters
 * @param cy [in] array size of y
 * @param y [out] function result vector
 * @return unix errno compatible code
 */
typedef int (*FN_BLNLSOLVER_OBJECTIVE)
    (uint32_t cx, const float* x, uint32_t cp, const float* params, uint32_t cy, float* y);

typedef struct {
    FILE *trace; //!< debug trace stream. initially set to stderr. You can set (FILE*)NUL to disable.
    FN_BLNLSOLVER_OBJECTIVE objective; //!< target function of optimization
    uint32_t cx, cy, cp;
    float* xInitial;
    float* xStepInitial;
    float* xStepConverged; // x convergence criterion
    float* yTarget;
    float* yTargetTolerances; // acceptable tolerances of y
    float* params;
} BLnlsolverconf_t, *pBLnlsolverconf_t;
typedef const BLnlsolverconf_t *pcBLnlsolverconf_t;

struct BLnlsolver;
typedef struct BLnlsolver *pBLnlsolver_t;
typedef const struct BLnlsolver *pcBLnlsolver_t;

typedef enum {
    BLnlsolverstatus_success, // successfully converged
    BLnlsolverstatus_objectiveerror, // the objective function returned error
    BLnlsolverstatus_notconverge
} BLnlsolverstatus_t;

/**
 * @brief constructor
 * 
 * @param cx 
 * @param cy 
 * @param cp 
 * @param func 
 * @return pBLnlsolver_t is a newly created instance.
 */
pBLnlsolver_t BLnlsolver_new(uint32_t cx, uint32_t cy, uint32_t cp, FN_BLNLSOLVER_OBJECTIVE func);

void BLnlsolver_delete(pBLnlsolver_t* ppobj);

/**
 * @brief get an accessor to configuration parameters
 * 
 * @param solver 
 * @return pBLnlsolverconf_t 
 */
pBLnlsolverconf_t BLnlsolver_conf(pBLnlsolver_t solver);

/**
 * @brief init simplex vertices
 * 
 * @param solver 
 * @return unix errno compatible code
 */
int BLnlsolver_init(pBLnlsolver_t solver);

/**
 * @brief execute 1 iteration of optimization step
 * 
 * @param solver 
 * @return int unix errno compatible number
 */
int BLnlsolver_execstep(pBLnlsolver_t solver);

int BLnlsolver_exec(pBLnlsolver_t solver, uint32_t iter);

/**
 * @brief get the current status
 * 
 * @param solver 
 * @return int 
 */
BLnlsolverstatus_t BLnlsolver_status(pcBLnlsolver_t solver);
#ifdef __cplusplus
}
#endif
#endif /* BLSOLVER_H_ */