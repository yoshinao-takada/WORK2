#include    "math/BLpoly.h"
#include    <assert.h>
#pragma region poly_value_calculation
BL1r32_t BLpolyr32(pcBLarray1D_t poly, BL1r32_t x)
{
    assert(sizeof(x) == poly->size[0]);
    BL1r32_t y = 0.0f;
    const BL1r32_t* ci = (const BL1r32_t*)BLarray1D_begin(poly);
    uint16_t i = poly->size[1];
    do {
        --i;
        y = x * y + ci[i];
    } while (i);
    return y;
}
BL1r64_t BLpolyr64(pcBLarray1D_t poly, BL1r64_t x)
{
    assert(sizeof(x) == poly->size[0]);
    BL1r64_t y = 0.0;
    const BL1r64_t* ci = (const BL1r64_t*)BLarray1D_begin(poly);
    uint16_t i = poly->size[1];
    do {
        --i;
        y = x * y + ci[i];
    } while (i);
    return y;
}

BL1c64_t BLpolyc64(pcBLarray1D_t poly, BL1c64_t x)
{
    assert(sizeof(x) == poly->size[0]);
    BL1c64_t y = CMPLXF(0.0f, 0.0f);
    const BL1c64_t* ci = (const BL1c64_t*)BLarray1D_begin(poly);
    uint16_t i = poly->size[1];
    do {
        --i;
        y = x * y + ci[i];
    } while (i);
    return y;
}

BL1c128_t BLpolyc128(pcBLarray1D_t poly, BL1c128_t x)
{
    assert(sizeof(x) == poly->size[0]);
    BL1c128_t y = CMPLX(0.0, 0.0);
    const BL1c128_t* ci = (const BL1c128_t*)BLarray1D_begin(poly);
    uint16_t i = poly->size[1];
    do {
        --i;
        y = x * y + ci[i];
    } while (i);
    return y;
}
#pragma endregion poly_value_calculation
#pragma region poly_mult_calculation
int BLpolymultr32(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod)
{
    assert((poly_prod->size[0] == poly0->size[0]) && (poly_prod->size[0] == poly1->size[0]));
    assert((poly_prod->size[1] == (poly0->size[1] + poly1->size[1] - 1)));
    int err = EXIT_SUCCESS;
    do {
        // clear poly_prod
        BL1r32_t* i_prod = (BL1r32_t*)BLarray1D_begin(poly_prod);
        for (uint16_t i = 0; i != poly_prod->size[1]; i++)
        {
            i_prod[i] = 0.0f;
        }

        // calculate product of the polynomials
        const BL1r32_t* i_poly0 = (const BL1r32_t*)BLarray1D_begin(poly0);
        const BL1r32_t* i_poly1 = (const BL1r32_t*)BLarray1D_begin(poly1);
        for (uint16_t i = 0; i != poly0->size[1]; i++)
        {
            for (uint16_t j = 0; j != poly1->size[1]; j++)
            {
                i_prod[i + j] += i_poly0[i] * i_poly1[j];
            }
        }
    } while (0);
    return err;
}

int BLpolymultr64(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod)
{
    assert((poly_prod->size[0] == poly0->size[0]) && (poly_prod->size[0] == poly1->size[0]));
    assert((poly_prod->size[1] == (poly0->size[1] + poly1->size[1] - 1)));
    int err = EXIT_SUCCESS;
    do {
        // clear poly_prod
        BL1r64_t* i_prod = (BL1r64_t*)BLarray1D_begin(poly_prod);
        for (uint16_t i = 0; i != poly_prod->size[1]; i++)
        {
            i_prod[i] = 0.0;
        }

        // calculate product of the polynomials
        const BL1r64_t* i_poly0 = (const BL1r64_t*)BLarray1D_begin(poly0);
        const BL1r64_t* i_poly1 = (const BL1r64_t*)BLarray1D_begin(poly1);
        for (uint16_t i = 0; i != poly0->size[1]; i++)
        {
            for (uint16_t j = 0; j != poly1->size[1]; j++)
            {
                i_prod[i + j] += i_poly0[i] * i_poly1[j];
            }
        }
    } while (0);
    return err;
}

int BLpolymultc64(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod)
{
    assert((poly_prod->size[0] == poly0->size[0]) && (poly_prod->size[0] == poly1->size[0]));
    assert((poly_prod->size[1] == (poly0->size[1] + poly1->size[1] - 1)));
    int err = EXIT_SUCCESS;
    do {
        // clear poly_prod
        BL1c64_t* i_prod = (BL1c64_t*)BLarray1D_begin(poly_prod);
        for (uint16_t i = 0; i != poly_prod->size[1]; i++)
        {
            i_prod[i] = CMPLXF(0.0f, 0.0f);
        }

        // calculate product of the polynomials
        const BL1c64_t* i_poly0 = (const BL1c64_t*)BLarray1D_begin(poly0);
        const BL1c64_t* i_poly1 = (const BL1c64_t*)BLarray1D_begin(poly1);
        for (uint16_t i = 0; i != poly0->size[1]; i++)
        {
            for (uint16_t j = 0; j != poly1->size[1]; j++)
            {
                i_prod[i + j] += i_poly0[i] * i_poly1[j];
            }
        }
    } while (0);
    return err;
}

int BLpolymultc128(pcBLarray1D_t poly0, pcBLarray1D_t poly1, pBLarray1D_t poly_prod)
{
    assert((poly_prod->size[0] == poly0->size[0]) && (poly_prod->size[0] == poly1->size[0]));
    assert((poly_prod->size[1] == (poly0->size[1] + poly1->size[1] - 1)));
    int err = EXIT_SUCCESS;
    do {
        // clear poly_prod
        BL1c128_t* i_prod = (BL1c128_t*)BLarray1D_begin(poly_prod);
        for (uint16_t i = 0; i != poly_prod->size[1]; i++)
        {
            i_prod[i] = CMPLX(0.0, 0.0);
        }

        // calculate product of the polynomials
        const BL1c128_t* i_poly0 = (const BL1c128_t*)BLarray1D_begin(poly0);
        const BL1c128_t* i_poly1 = (const BL1c128_t*)BLarray1D_begin(poly1);
        for (uint16_t i = 0; i != poly0->size[1]; i++)
        {
            for (uint16_t j = 0; j != poly1->size[1]; j++)
            {
                i_prod[i + j] += i_poly0[i] * i_poly1[j];
            }
        }
    } while (0);
    return err;
}

#pragma endregion poly_mult_calculation
#define MOVE_PTR(ptr0, ptr1) { BLSAFEFREE(&ptr0); ptr0 = ptr1; ptr1 = NULL; }
static int ButterworthPolynomialF(
    uint32_t order,
    const BL1r32_t* poly_component,
    pBLarray1D_t* pppoly
) {
    const uint32_t poly_component_2nd_order_count = order / 2;
    int err = EXIT_SUCCESS;
    int poly_component_index = 0;
    pBLarray1D_t poly0 = NULL, poly1 = NULL, poly2 = NULL;
    uint16_t cnumsize = 8;
    BL2u16_t size0 = { cnumsize, 1 };
    BL2u16_t size1 = { cnumsize, 2 };
    BL2u16_t size2 = { cnumsize, 3 };
    do {
        if ((order & 1) != 0)
        { // odd order, (1 + s) factor must be processed.
            BLarray1D_alloc(poly0, size0);
            BLarray1D_alloc(poly1, size0);
            BLarray1D_alloc(poly2, size1);
            if (!poly0 || !poly1 || !poly2)
            {
                err = ENOMEM;
                break;
            }
            *(BL1r32_t*)BLarray1D_begin(poly0) = CMPLXF(1.0f, 0.0f);
            *(BL1r32_t*)BLarray1D_begin(poly1) = CMPLXF(1.0f, 0.0f);
            BL1r32_t* i_poly2 = (BL1r32_t*)BLarray1D_begin(poly2);
            i_poly2[poly_component_index] = poly_component[poly_component_index];
            poly_component_index++;
            i_poly2[poly_component_index] = poly_component[poly_component_index];
            poly_component_index++;
            if (EXIT_SUCCESS != (err = BLpolymultr32(poly1, poly2, poly0)))
            {
                break;
            }
        }
        for (uint32_t i = 0; i < poly_component_2nd_order_count; i++)
        {
            MOVE_PTR(poly1, poly0); // move poly0 to poly1
            BLSAFEFREE(&poly2);
            BLarray1D_alloc(poly2, size2);
            BL1r32_t* i_poly2 = (BL1r32_t*)BLarray1D_begin(poly2);
            for (uint16_t j = 0; j < poly2->size[1]; j++)
            {
                i_poly2[j] = poly_component[poly_component_index++];
            }
            size0[1] = poly1->size[1] + size2[1];
            BLarray1D_alloc(poly0, size0);
            if (EXIT_SUCCESS != (err = BLpolymultr32(poly1, poly2, poly0)))
            {
                break;
            }
        }
    } while (0);
    BLSAFEFREE(&poly1);
    BLSAFEFREE(&poly2);
    if (err)
    {
        *pppoly = poly0;
    }
    else
    {
        *pppoly = NULL;
        BLSAFEFREE(&poly0);
    }
    return err;
}

const BL1r32_t* BLpolybutterworthcoeffs(uint32_t order)
{
    assert((order >= 1) && (order <= 8));
    static const BL1r32_t c0[] = { 1.0f, 1.0f };
    static const BL1r32_t c1[] = { 1.0f, 1.4142f, 1.0f };
    static const BL1r32_t c2[] = {{  1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }};
    static const BL1r32_t c3[] = {{ 1.0f, 0.765f, 1.0f } , { 1.0f, 1.848f, 1.0f }};
    static const BL1r32_t c4[] = {{ 1.0f, 1.0f }, { 1.0f, 0.618f, 1.0f }, { 1.0f, 1.618f, 1.0f }};
    static const BL1r32_t c5[] =
    {{ 1.0f, 0.518f, 1.0f }, { 1.0f, 1.4142f, 1.0f }, { 1.0f, 1.932f, 1.0f }};
    static const BL1r32_t c6[] = 
    {{ 1.0f, 1.0f }, { 1.0f, 0.445f, 1.0f }, { 1.0f, 1.247f, 1.0f }, { 1.0f, 1.802f, 1.0f }};
    static const BL1r32_t c7[] = 
    {{ 1.0f, 0.39f, 1.0f }, { 1.0f, 1.111f, 1.0f }, { 1.0f, 1.6663f, 1.0f }, { 1.0f, 1.962f, 1.0f }};
    static const BL1r32_t* c[] = { c0, c1, c2, c3, c4, c5, c6, c7 };
    return c[order - 1];
}

int BLpolybutterworth(uint32_t order, uint32_t rnumsize, pBLarray1D_t* pppoly)
{
    int err = ButterworthPolynomialF(order, BLpolybutterworthcoeffs(order), pppoly);
    return err;
}
