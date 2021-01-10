#include    "base/BLarray.h"
#include    <memory.h>
#include    <stdio.h>

#define SRC4X4_0 \
{ \
    {0,0}, {1,0}, {2,0}, {3,0}, \
    {0,1}, {1,1}, {2,1}, {3,1}, \
    {0,2}, {1,2}, {2,2}, {3,2}, \
    {0,3}, {1,3}, {2,3}, {3,3} \
}

#define SRC4X4_1 \
{ \
    {0,0}, {11,0}, {22,0}, {33,0}, \
    {0,11}, {11,11}, {22,11}, {33,11}, \
    {0,22}, {11,22}, {22,22}, {33,22}, \
    {0,33}, {11,33}, {22,33}, {33,33} \
}

#define REF4X4_0 \
{ \
    {0,0}, {1,0}, {2,0}, {3,0}, \
    {0,1}, {0,0}, {11,0}, {3,1}, \
    {0,2}, {0,11}, {11,11}, {3,2}, \
    {0,3}, {1,3}, {2,3}, {3,3} \
}

#define REF4X4_1 \
{ \
    {0,0}, {1,0}, {0,22}, {11,22}, \
    {0,1}, {1,1}, {0,33}, {11,33}, \
    {0,2}, {1,2}, {2,2}, {3,2}, \
    {0,3}, {1,3}, {2,3}, {3,3} \
}

#define REF2X2_0 \
{ \
    {2,1}, {3,1}, \
    {2,2}, {3,2} \
}

#define REF2X2_1 \
{ \
    {0,2}, {1,2}, \
    {0,3}, {1,3}, \
}

/*!
\brief compare two arrays of BL2u32_t.
\param x0 [in] beginning of the 1st array
\param x1 [in] beginning of the 2nd array
\param size [in] 2D array size
\return EXIT_SUCCESS: equal, EXIT_FAILURE: NOT equal
*/
int AreEqual(const BL2u32_t* x0, const BL2u32_t* x1, const BL2u32_t size);

int UTAreEqual();

/*!
\brief unit test
\return EXIT_SUCCESS or EXIT_FAILURE
*/
int UTcopy2D_4X4_to_2X2();
int UTcopy2D_4X4_to_4X4();
