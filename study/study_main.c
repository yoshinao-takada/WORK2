#include    "study/UTmargincopy2D.h"
#include    "study/UTsat.h"
#include    "study/UTfilter2D.h"

int main(int argc, const char* argv[])
{
    int result = EXIT_SUCCESS;
    do {
        fprintf(stdout, "==== UTmargincopy2D ====\n");
        result = UTmargincopy2D_vertical_cyclic();
        fprintf(stdout, "UTmargincopy2D_vertical_cyclic(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        result = UTmargincopy2D_fixed();
        fprintf(stdout, "UTmargincopy2D_fixed(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        result = UTmargincopy2D_extend();
        fprintf(stdout, "UTmargincopy2D_extend(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        result = UTmargincopy2D_cyclic();
        fprintf(stdout, "UTmargincopy2D_cyclic(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        // fprintf(stdout, "==== UTsat ====\n");
        // result = UTsat_i16_from_i8();
        // fprintf(stdout, "UTsat_i16_from_i8(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        // result = UTsat_u16_from_u8();
        // fprintf(stdout, "UTsat_u16_from_u8(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        // result = UTsat_i32_from_i8();
        // fprintf(stdout, "UTsat_i32_from_i8(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        // result = UTsat_u32_from_u8();
        // fprintf(stdout, "UTsat_u32_from_u8(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        // result = UTsat_r32_from_r32();
        // fprintf(stdout, "UTsat_r32_from_r32(): %s\n", (result == EXIT_SUCCESS) ? "SUCCESS" : "FAILURE");
        fprintf(stdout, "==== UTfilter2D ==== \n");
        result = UTfilter2D_box();
        result = UTfilter2D_given_kernel();
    } while (0);
    return result;
}