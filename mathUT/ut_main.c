#include    "base/BLbase.h"

int sa();

int main(int argc, char* argv[])
{
    int err_each = EXIT_SUCCESS;
    int err = err_each;
    do {
        err |= (err_each = sa());
        UT_SHOW(stdout, "sa", 0, err_each);
    } while (0);
    UT_SHOW(stdout, "main", 0, err);
    return err;
}