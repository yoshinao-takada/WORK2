#include "base/BLnlsolver.h"

typedef struct BLvarobj {
    float* var; // variable vector of objective function
    float evalResult; // evaluated error value
} BLvarobj_t, *pBLvarobj_t;
typedef const BLvarobj_t *pcBLvarobj_t;

#pragma region BLvarobj_support_functions
static int BLvarobj_compare(const void* varobj0_, const void* varobj1_)
{
    int result = 0;
    pcBLvarobj_t varobj0 = (pcBLvarobj_t)varobj0_;
    pcBLvarobj_t varobj1 = (pcBLvarobj_t)varobj1_;
    if (varobj0->evalResult < varobj1->evalResult)
    {
        result = -1;
    }
    else if (varobj0->evalResult > varobj1->evalResult)
    {
        result = 1;
    }
    return result;
}

static void BLvarobj_sort(pcBLvarobj_t begin, pcBLvarobj_t end)
{
    size_t nmemb = end - begin;
    size_t size = sizeof(BLvarobj_t);
    qsort(begin, nmemb, size, BLvarobj_compare);
}

static void BLvarobj_swap(pBLvarobj_t varobj0, pBLvarobj_t varobj1)
{
    BLvarobj_t temp = { varobj0->var, varobj0->evalResult };
    varobj0->var = varobj1->var;
    varobj0->evalResult = varobj1->evalResult;
    varobj1->var = temp.var;
    varobj1->evalResult = temp.evalResult;
}

#define ADD_FLOATS(a,b,count) for (int i = 0; i < ((int)count); i++) { a[i] += b[i]; }

#define MULTPLYSCALAR_FLOATS(a,s,count) for (int i = 0; i < ((int)count); i++) { a[i] *= s; }

/**
 * @brief calculate the centroid of var part of the array of BLvarobj_t
 * @param begin [in] begin iterator
 * @param end [in] end iterator (next of the last element)
 * @param centroid [out] centroid->evalResult is not updated.
 */
static void BLvarobj_centroid(uint32_t varsize, pcBLvarobj_t begin, pcBLvarobj_t end, pBLvarobj_t centroid)
{
    float* centroid_var = centroid->var;
    FILL_FLOATS(centroid_var, varsize, 0.0f);
    float rcp_varsize = 1.0f/(float)varsize;
    for (pcBLvarobj_t i_varobj = begin; i_varobj != end; i_varobj++)
    {
        ADD_FLOATS(centroid_var, i_varobj->var, (int)varsize);
    }
    MULTPLYSCALAR_FLOATS(centroid_var, rcp_varsize, (int)varsize);
}

static void BLvarobj_newpoint(
    uint32_t varsize, pcBLvarobj_t centroid, pcBLvarobj_t worst, pBLvarobj_t newpoint, float rho)
{
    float* xnew = newpoint->var;
    const float* xo = centroid->var;
    const float* xn_1 = worst->var;
    for (uint32_t k = 0; k < varsize; k++)
    {
        xnew[k] = xo[k] + rho * (xo[k] - xn_1[k]);
    }
}

static void BLvarobj_shrink(uint32_t varsize, pBLvarobj_t varobj, float rho)
{
    const float* xbest = varobj[0].var;
    for (uint32_t j = 1; j <= varsize; j++)
    {
        float* xj = varobj[j].var;
        for (uint32_t k = 0; k < varsize; k++)
        {
            xj[k] = xbest[k] + rho * (xj[k] - xbest[k]);
        }
    }
}
#pragma endregion BLvarobj_support_functions
#define BLnlsolver_trace(solver,...) do { \
    if (solver->conf.trace == NULL) break; \
    fprintf(solver->conf.trace, __VA_ARGS__); \
} while (0)

struct BLnlsolver {
    BLnlsolverconf_t conf;
    pBLvarobj_t vertices; // simplex vertices
    float *yWork;
    uint32_t iterCount; // iteration counter
    int objectiveReturnCode; // return code of objective function lastest evaluation
    float rhoR; // reflection point parameter
    float rhoE; // expansion point parameter
    float rhoC; // contraction pont parameter
    float rhoS; // simplex shrinking factor
    uint32_t indexR;
    uint32_t indexE;
    uint32_t indexC;
    uint32_t indexS;
    uint32_t indexCentroid;
};

pBLnlsolver_t BLnlsolver_new(uint32_t cx, uint32_t cy, uint32_t cp, FN_BLNLSOLVER_OBJECTIVE func)
{
    uint32_t verticesDim = cx + 1 + 5; // saved vertices: cx + 1, Reflection, Expansion, Contraction, Shrinking, centroid
    pBLnlsolver_t pThis = (pBLnlsolver_t)malloc(sizeof(struct BLnlsolver));
    pThis->vertices = (pBLvarobj_t)calloc(verticesDim, sizeof(BLvarobj_t)); // [0..cx]: simplex vertices, [cx + 1]: work vertex
    pThis->yWork = (float*)calloc(cy, sizeof(float));
    pThis->conf.xInitial = (float*)calloc(cx, sizeof(float));
    pThis->conf.xStepInitial = (float*)calloc(cx, sizeof(float));
    pThis->conf.xStepConverged = (float*)calloc(cx, sizeof(float));
    pThis->conf.yTarget = (float*)calloc(cy, sizeof(float));
    pThis->conf.yTargetTolerances = (float*)calloc(cy, sizeof(float));
    pThis->conf.params = (float*)calloc(cp, sizeof(float));
    for (uint32_t i = 0; i < verticesDim; i++)
    {
        pThis->vertices[i].var = (float*)calloc(cx, sizeof(float));
        pThis->vertices[i].evalResult = 0.0f;
    }
    pThis->conf.trace = NULL;
    pThis->conf.cx = cx;
    pThis->conf.cy = cy;
    pThis->conf.cp = cp;
    pThis->iterCount = 0;
    pThis->objectiveReturnCode = EXIT_SUCCESS;
    pThis->rhoR = 0.7f;
    pThis->rhoE = 1.5f;
    pThis->rhoC = 0.25f;
    pThis->rhoS = 0.7f;
    pThis->indexR = cx + 1;
    pThis->indexE = cx + 2;
    pThis->indexC = cx + 3;
    pThis->indexS = cx + 4;
    return pThis;
}

void BLnlsolver_delete(pBLnlsolver_t* ppobj)
{
    if (ppobj)
    {
        pBLnlsolver_t pobj = *ppobj;
        int verticesDim = pobj->conf.cx + 1 + 5; // saved vertices: cx + 1, Reflection, Expansion, Contraction, Shrinking
        for (int i = 0; i < verticesDim; i++)
        {
            free(pobj->vertices[i].var);
        }
        free(pobj->conf.params);
        free(pobj->conf.yTargetTolerances);
        free(pobj->conf.yTarget);
        free(pobj->conf.xStepConverged);
        free(pobj->conf.xStepInitial);
        free(pobj->conf.xInitial);
        free(pobj->yWork);
        free(pobj->vertices);
        free(pobj);
        *ppobj = NULL;
    }
}

pBLnlsolverconf_t BLnlsolver_conf(pBLnlsolver_t solver)
{
    return &solver->conf;
}

#define SUBTRACT_FLOATS(a,b,count) do {for (int i = 0; i < count; i++) { a[i] -= b[i]; }} while (0)

static int BLnlsolver_eval(pBLnlsolver_t solver, uint32_t varIndex)
{
    int err = EXIT_SUCCESS;
    do {
        solver->objectiveReturnCode = solver->conf.objective(
            solver->conf.cx, solver->vertices[varIndex].var,
            solver->conf.cp, solver->conf.params,
            solver->conf.cy, solver->yWork);
        if (EXIT_SUCCESS != err)
        {
            break;
        }
        SUBTRACT_FLOATS(solver->yWork, solver->conf.yTarget, solver->conf.cy);
        solver->vertices[varIndex].evalResult = 0.0f;
        for (int i = 0; i < solver->conf.cy; i++)
        {
            solver->vertices[varIndex].evalResult += (solver->yWork[i] * solver->yWork[i]);
        }
    } while (0);
    return err;
}

int BLnlsolver_init(pBLnlsolver_t solver)
{
    int err = EXIT_SUCCESS;
    do {
        size_t xVectorBytes = (size_t)(solver->conf.cx * sizeof(float)); // x vector byte count
        int simplexVerticesCount = solver->conf.cx + 1;
        for (int i = 0; i < simplexVerticesCount; i++)
        {
            float* vertex_var = solver->vertices[i].var;
            memcpy(vertex_var, solver->conf.xInitial, xVectorBytes);
            if (i != 0)
            {
                vertex_var[i-1] += solver->conf.xStepInitial[i-1];
            }
            if (EXIT_SUCCESS != (err = BLnlsolver_eval(solver, i)))
            {
                break;
            }
        }
        if (err) break;
        BLvarobj_sort(solver->vertices, solver->vertices + simplexVerticesCount);
    } while (0);
    return err;
}

static int BLnlsolver_adoptreflection(pBLnlsolver_t solver)
{
    int err = EXIT_SUCCESS;
    do {
        if ((solver->vertices[solver->indexCentroid].evalResult <= solver->vertices[solver->indexR].evalResult) &&
            (solver->vertices[solver->indexR].evalResult < solver->vertices[solver->conf.cx].evalResult))
        {
            BLvarobj_swap(solver->vertices + solver->indexR, solver->vertices + solver->conf.cx);
            BLvarobj_sort(solver->vertices, solver->vertices + solver->indexR);
        }
        else
        {
            err = ERANGE;
        }
    } while (0);
    return err;
}

static int BLnlsolver_adoptexpansion(pBLnlsolver_t solver)
{
    int err = EXIT_SUCCESS;
    do {
        if (solver->vertices[solver->indexE].evalResult < solver->vertices[solver->indexR].evalResult)
        {
            BLvarobj_swap(solver->vertices + solver->indexE, solver->vertices + solver->conf.cx);
            BLvarobj_sort(solver->vertices, solver->vertices + solver->indexR);
        }
        else
        {
            err = ERANGE;
        }
    } while (0);
    return err;
}

static int BLnlsolver_adoptcontraction(pBLnlsolver_t solver)
{
    int err = EXIT_SUCCESS;
    do {
        if (solver->vertices[solver->indexC].evalResult < solver->vertices[solver->conf.cx].evalResult)
        {
            BLvarobj_swap(solver->vertices + solver->indexC, solver->vertices + solver->conf.cx);
            BLvarobj_sort(solver->vertices, solver->vertices + solver->indexR);
        }
        else
        {
            err = ERANGE;
        }
    } while (0);
    return err;
}

int BLnlsolver_execstep(pBLnlsolver_t solver)
{
    int err = EXIT_SUCCESS;
    do {
        // Evaluate reflection point
        BLvarobj_centroid(solver->conf.cx,
            solver->vertices, solver->vertices + solver->conf.cx, solver->vertices + solver->indexCentroid);
        BLvarobj_newpoint(solver->conf.cx,
            solver->vertices + solver->indexCentroid, solver->vertices + solver->conf.cx,
            solver->vertices + solver->indexR, solver->rhoR);
        if ((EXIT_SUCCESS != (err = BLnlsolver_eval(solver, solver->indexCentroid))) ||
            (EXIT_SUCCESS != (err = BLnlsolver_eval(solver, solver->indexR))))
        {
            break;
        }
        if (EXIT_SUCCESS == BLnlsolver_adoptreflection(solver))
        { // reflection point was good!
            break;
        }
        err = EXIT_SUCCESS;

        // evaluate expansion point
        BLvarobj_newpoint(solver->conf.cx,
            solver->vertices + solver->indexCentroid, solver->vertices + solver->conf.cx,
            solver->vertices + solver->indexE, solver->rhoE);
        if (EXIT_SUCCESS == BLnlsolver_adoptexpansion(solver))
        { // expansion point was good!
            break;
        }
        err = EXIT_SUCCESS;

        // evaluate contract point
        BLvarobj_newpoint(solver->conf.cx,
            solver->vertices + solver->indexCentroid, solver->vertices + solver->conf.cx,
            solver->vertices + solver->indexC, solver->rhoC);
        if (EXIT_SUCCESS == BLnlsolver_adoptcontrction(solver))
        { // contraction point was good!
            break;
        }
        err = EXIT_SUCCESS;

        // shrinking
        BLvarobj_shrink(solver->conf.cx, solver->vertices, solver->rhoS);
        for (uint32_t k = 0; k < solver->indexR; k++)
        {
            if (EXIT_SUCCESS != (err = BLnlsolver_eval(solver, k)))
            {
                break;
            }
        }
        if (err) break;
        BLvarobj_sort(solver->vertices, solver->vertices + solver->indexR);
    } while (0);
    return err;
}

static int BLnlsolver_x_converged(pBLnlsolver_t solver)
{
    int err = EXIT_SUCCESS;
    do {
        // check if all x are sufficiently close to their centroid.
        const float* xo = solver->vertices[solver->indexCentroid].var;
        for (uint32_t vertexIndex = 0; vertexIndex != solver->conf.cx; vertexIndex++)
        {
            const float* xvert = solver->vertices[vertexIndex].var;
            for (uint32_t k = 0; k < solver->conf.cx; k++)
            {
                if (fabsf(xo[k] - xvert[k]) > solver->conf.xStepConverged[k])
                {
                    err = ERANGE;
                    break;
                }
            }
            if (err) break;
        }
    } while (0);
    return err;
}

static int BLnlsolver_y_converged(pBLnlsolver_t solver)
{ // check if the best y is sufficiently close to yTarget
    int err = EXIT_SUCCESS;
    do {
        solver->objectiveReturnCode = solver->conf.objective(solver->conf.cx, solver->vertices[0].var,
            solver->conf.cp, solver->conf.params, solver->conf.cy, solver->yWork);
        SUBTRACT_FLOATS(solver->yWork, solver->conf.yTarget, solver->conf.cy);
        for (uint32_t k = 0; k < solver->conf.cy; k++)
        {
            if (solver->yWork[k] > solver->conf.yTargetTolerances[k])
            {
                err = ERANGE;
                break;
            }
        }
    } while (0);
    return err;
}

int BLnlsolver_exec(pBLnlsolver_t solver, uint32_t iter)
{
    int err = EXIT_SUCCESS;
    solver->iterCount = iter;
    do {
        if (EXIT_SUCCESS != (err = BLnlsolver_execstep(solver)))
        {
            break;
        }
        if (EXIT_SUCCESS == (err = BLnlsolver_x_converged(solver)))
        {
            break;
        }
        if (EXIT_SUCCESS == (err = BLnlsolver_y_converged(solver)))
        {
            break;
        }
    } while (--solver->iterCount);
    return err;
}

BLnlsolverstatus_t BLnlsolver_status(pcBLnlsolver_t solver)
{
    if (solver->objectiveReturnCode)
    {
        return BLnlsolverstatus_objectiveerror;
    }
    else if (BLnlsolver_x_converged(solver) && BLnlsolver_y_converged(solver))
    {
        return BLnlsolverstatus_notconverge;
    }
    return BLnlsolverstatus_success;
}
