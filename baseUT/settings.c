#include    "base/BLsettings.h"
#include    "base/BLbase.h"
#define TEST_DATA0  "settings-test0.txt"
#define TEST_DATA1  "settings-test1.txt"

int settings_test0();
int settings_test1();

int settings()
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = settings_test0()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (EXIT_SUCCESS != (err = settings_test1()))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    UT_SHOW(stderr,  __FUNCTION__, __LINE__, err);
    return err;
}

int settings_test0()
{
    int err = EXIT_SUCCESS;
    BLsettings_t settings = {
        0, NULL,
        0, NULL, NULL, NULL
    };
    int int_values[3];
    float float_values[3];
    do {
        if (EXIT_SUCCESS != (err = BLsettings_read(&settings, TEST_DATA0)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLsettings_write(&settings, stderr);
        const char* stringparam = NULL;
        stringparam = Blsettings_getstring(&settings, "invalid_key");
        if (stringparam)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        stringparam = Blsettings_getstring(&settings, "group0.end");
        if (stringparam)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        stringparam = Blsettings_getstring(&settings, "group0.string_key");
        if (strcmp("\"This is a string value\"", stringparam))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        stringparam = Blsettings_getstring(&settings, "group0.string_key2");
        if (strcmp("This is a non-quoted value", stringparam))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if ((EXIT_SUCCESS != (err = BLsettings_getint(&settings, "group0.int_key1", int_values))) ||
            (int_values[0] != 100))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if ((EXIT_SUCCESS != (err = BLsettings_getint2D(&settings, "group0.int_key2", int_values))) ||
            (int_values[0] != 101) || (int_values[1] != 102))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
        if ((EXIT_SUCCESS != (err = BLsettings_getint3D(&settings, "group0.int_key3", int_values))) ||
            (int_values[0] != 103) || (int_values[1] != 104) || (int_values[2] != -105))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err == EXIT_FAILURE));
        }
        if ((EXIT_SUCCESS != (err = BLsettings_getfloat(&settings, "group0.float_key1", float_values))) ||
            !BL_EQ_F(100.0f, float_values[0], 1.0e-5f))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
            fprintf(stderr, "float_values {%f, %f, %f}\n",
                float_values[0], float_values[1], float_values[2]);
        if ((EXIT_SUCCESS != (err = BLsettings_getfloat2D(&settings, "group0.float_key2", float_values))) ||
            !BL_EQ_F(100.1f, float_values[0], 1.0e-5f) || !BL_EQ_F(100.2f, float_values[1], 1.0e-5f))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
            fprintf(stderr, "float_values {%f, %f, %f}\n",
                float_values[0], float_values[1], float_values[2]);
        if ((EXIT_SUCCESS != (err = BLsettings_getfloat3D(&settings, "group0.float_key3", float_values))) ||
            !BL_EQ_F(100.3f, float_values[0], 1.0e-5f) || !BL_EQ_F(-100.4f, float_values[1], 1.0e-5f) || !BL_EQ_F(-1.25e-12f, float_values[2], 1.0e-5f))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, (err = EXIT_FAILURE));
        }
            fprintf(stderr, "float_values {%f, %f, %f}\n",
                float_values[0], float_values[1], float_values[2]);
    } while (0);
    BLsettings_clean(&settings);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}

int settings_test1()
{
    int err = EXIT_SUCCESS;
    BLsettings_t settings = {
        0, NULL,
        0, NULL, NULL, NULL
    };
    do {
        if (EXIT_SUCCESS != (err = BLsettings_read(&settings, TEST_DATA0)))
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLsettings_clean(&settings);
    UT_SHOW(stderr, __FUNCTION__, __LINE__, err);
    return err;
}
