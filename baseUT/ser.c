#include    "base/BLser.h"
#include    "base/BLsv.h"
#include    <string.h>
#include    "base/BLarray1D.h"

static int UT1i08();
static int UT1i16();
static int UT1i32();
static int UT1r32();
static int UT1r64();
static int UT2i08();
static int UT2i16();
static int UT2i32();
static int UT2r32();
static int UT2r64();
static int UT3i08();
static int UT3i16();
static int UT3i32();
static int UT3r32();
static int UT3r64();
static int UT4i08();
static int UT4i16();
static int UT4i32();
static int UT4r32();
static int UT4r64();
static int UT6i08();
static int UT6i16();
static int UT6i32();
static int UT6r32();
static int UT6r64();
static int UT8i08();
static int UT8i16();
static int UT8i32();
static int UT8r32();
static int UT8r64();
static int UTstri();
static int UTai08();
static int UTai16();
static int UTai32();
static int UTar32();
static int UTar64();

#define RUNTEST(subfunc,err_) if (EXIT_SUCCESS != (err_ = subfunc())) { \
    UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err_); }

int ser()
{
    int err = EXIT_SUCCESS;
    do {
        RUNTEST(UT1i08, err);
        RUNTEST(UT1i16, err);
        RUNTEST(UT1i32, err);
        RUNTEST(UT1r32, err);
        RUNTEST(UT1r64, err);
        RUNTEST(UT2i08, err);
        RUNTEST(UT2i16, err);
        RUNTEST(UT2i32, err);
        RUNTEST(UT2r32, err);
        RUNTEST(UT2r64, err);
        RUNTEST(UT3i08, err);
        RUNTEST(UT3i16, err);
        RUNTEST(UT3i32, err);
        RUNTEST(UT3r32, err);
        RUNTEST(UT3r64, err);
        RUNTEST(UT4i08, err);
        RUNTEST(UT4i16, err);
        RUNTEST(UT4i32, err);
        RUNTEST(UT4r32, err);
        RUNTEST(UT4r64, err);
        RUNTEST(UT6i08, err);
        RUNTEST(UT6i16, err);
        RUNTEST(UT6i32, err);
        RUNTEST(UT6r32, err);
        RUNTEST(UT6r64, err);
        RUNTEST(UT8i08, err);
        RUNTEST(UT8i16, err);
        RUNTEST(UT8i32, err);
        RUNTEST(UT8r32, err);
        RUNTEST(UT8r64, err);
        RUNTEST(UTstri, err);
        RUNTEST(UTai08, err);
        RUNTEST(UTai16, err);
        RUNTEST(UTai32, err);
        RUNTEST(UTar32, err);
        RUNTEST(UTar64, err);
    } while (0);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}

static int UT1i08()
{
    static const uint16_t ref_serimg_byte_count = 5;
    int err = EXIT_SUCCESS;
    BL1i8_t src0 = 0x55;
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_1i8);
    BLserializable_estsize_f deserest = BLserializable_deserialize_estimator(BLserializable_1i8);
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_1i8);
    BLserializable_convert_f deserializer = BLserializable_deserializer(BLserializable_1i8);
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(&src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != 1)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (*(BL1i8_t*)deserimg != src0)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT1i16()
{
    static const uint16_t ref_serimg_byte_count = 6;
    int err = EXIT_SUCCESS;
    BL1i16_t src0 = 0x55aa;
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_1i16);
    BLserializable_estsize_f deserest = BLserializable_deserialize_estimator(BLserializable_1i16);
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_1i16);
    BLserializable_convert_f deserializer = BLserializable_deserializer(BLserializable_1i16);
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((uint8_t*)&src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != 2)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (*(BL1i16_t*)deserimg != src0)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT1i32()
{
    static const uint16_t ref_serimg_byte_count = 8;
    int err = EXIT_SUCCESS;
    BL1i32_t src0 = 0x55aafeff;
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_1i32);
    BLserializable_estsize_f deserest = BLserializable_deserialize_estimator(BLserializable_1i32);
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_1i32);
    BLserializable_convert_f deserializer = BLserializable_deserializer(BLserializable_1i32);
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((uint8_t*)&src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL1i32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (*(BL1i32_t*)deserimg != src0)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT1r32()
{
    static const uint16_t ref_serimg_byte_count = 8;
    int err = EXIT_SUCCESS;
    BL1r32_t src0 = -1.8833e-5f;
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_1r32);
    BLserializable_estsize_f deserest = BLserializable_deserialize_estimator(BLserializable_1r32);
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_1r32);
    BLserializable_convert_f deserializer = BLserializable_deserializer(BLserializable_1r32);
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((uint8_t*)&src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL1r32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (*(BL1r32_t*)deserimg != src0)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT1r64()
{
    static const uint16_t ref_serimg_byte_count = 12;
    int err = EXIT_SUCCESS;
    BL1r64_t src0 = -5.550033883333e-13;
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_1r64);
    BLserializable_estsize_f deserest = BLserializable_deserialize_estimator(BLserializable_1r64);
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_1r64);
    BLserializable_convert_f deserializer = BLserializable_deserializer(BLserializable_1r64);
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((uint8_t*)&src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL1r64_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (*(BL1r64_t*)deserimg != src0)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT2i08()
{
    static const uint16_t ref_serimg_byte_count = 6;
    int err = EXIT_SUCCESS;
    BL2i8_t src0 = { 0x55, 0xfe };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_2i8);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_2i8);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL2i8_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int8_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT2i16()
{
    static const uint16_t ref_serimg_byte_count = 8;
    int err = EXIT_SUCCESS;
    BL2i16_t src0 = { 0x55fe, 0xfe55 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_2i16);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_2i16);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL2i16_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int16_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT2i32()
{
    static const uint16_t ref_serimg_byte_count = 12;
    int err = EXIT_SUCCESS;
    BL2i32_t src0 = { 0xfe5555fe, 0x55fefe55 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_2i32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_2i32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL2i32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT2r32()
{
    static const uint16_t ref_serimg_byte_count = 12;
    int err = EXIT_SUCCESS;
    BL2r32_t src0 = { 1.5858e05f, -0.153825e-5f };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_2r32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_2r32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL2r32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT2r64()
{
    static const uint16_t ref_serimg_byte_count = 20;
    int err = EXIT_SUCCESS;
    BL2r64_t src0 = { 1.5858e50, -0.153825e-15 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_2r64);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_2r64);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL2r64_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r64_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT3i08()
{
    static const uint16_t ref_serimg_byte_count = 7;
    int err = EXIT_SUCCESS;
    BL3i8_t src0 = { 0x55, 0xfe, 0x31 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_3i8);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_3i8);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL3i8_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int8_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT3i16()
{
    static const uint16_t ref_serimg_byte_count = 10;
    int err = EXIT_SUCCESS;
    BL3i16_t src0 = { 0x55fe, 0xfe55, 0x3030 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_3i16);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_3i16);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL3i16_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int16_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT3i32()
{
    static const uint16_t ref_serimg_byte_count = 16;
    int err = EXIT_SUCCESS;
    BL3i32_t src0 = { 0xfe5555fe, 0x55fefe55, 0x30300303 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_3i32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_3i32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL3i32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT3r32()
{
    static const uint16_t ref_serimg_byte_count = 16;
    int err = EXIT_SUCCESS;
    BL3r32_t src0 = { 1.5858e05f, -0.153825e-5f, 25.0e-3f };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_3r32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_3r32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL3r32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT3r64()
{
    static const uint16_t ref_serimg_byte_count = 28;
    int err = EXIT_SUCCESS;
    BL3r64_t src0 = { 1.5858e50, -0.153825e-15, 0.01 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_3r64);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_3r64);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL3r64_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r64_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT4i08()
{
    static const uint16_t ref_serimg_byte_count = 8;
    int err = EXIT_SUCCESS;
    BL4i8_t src0 = { 0x55, 0xfe, 0x31, 0x01 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_4i8);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_4i8);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL4i8_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int8_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT4i16()
{
    static const uint16_t ref_serimg_byte_count = 12;
    int err = EXIT_SUCCESS;
    BL4i16_t src0 = { 0x55fe, 0xfe55, 0x3030, 0x0101 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_4i16);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_4i16);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL4i16_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int16_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT4i32()
{
    static const uint16_t ref_serimg_byte_count = 20;
    int err = EXIT_SUCCESS;
    BL4i32_t src0 = { 0xfe5555fe, 0x55fefe55, 0x30300303, 0x01010101 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_4i32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_4i32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL4i32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT4r32()
{
    static const uint16_t ref_serimg_byte_count = 20;
    int err = EXIT_SUCCESS;
    BL4r32_t src0 = { 1.5858e05f, -0.153825e-5f, 25.0e-3f, 1.0f };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_4r32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_4r32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL4r32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT4r64()
{
    static const uint16_t ref_serimg_byte_count = 36;
    int err = EXIT_SUCCESS;
    BL4r64_t src0 = { 1.5858e50, -0.153825e-15, 0.01, 1.0 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_4r64);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_4r64);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL4r64_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r64_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT6i08()
{
    static const uint16_t ref_serimg_byte_count = 10;
    int err = EXIT_SUCCESS;
    BL6i8_t src0 = { 0x55, 0xfe, 0x31, 0x01, 0x02, 0x03 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_6i8);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_6i8);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL6i8_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int8_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT6i16()
{
    static const uint16_t ref_serimg_byte_count = 16;
    int err = EXIT_SUCCESS;
    BL6i16_t src0 = { 0x55fe, 0xfe55, 0x3030, 0x0101, 0x0202, 0x0303 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_6i16);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_6i16);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL6i16_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int16_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT6i32()
{
    static const uint16_t ref_serimg_byte_count = 28;
    int err = EXIT_SUCCESS;
    BL6i32_t src0 = { 0xfe5555fe, 0x55fefe55, 0x30300303, 0x01010101, 0x02020202, 0x03030303 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_6i32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_6i32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL6i32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT6r32()
{
    static const uint16_t ref_serimg_byte_count = 28;
    int err = EXIT_SUCCESS;
    BL6r32_t src0 = { 1.5858e05f, -0.153825e-5f, 25.0e-3f, 1.0f, -1.0f, -2.0f };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_6r32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_6r32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL6r32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT6r64()
{
    static const uint16_t ref_serimg_byte_count = 52;
    int err = EXIT_SUCCESS;
    BL6r64_t src0 = { 1.5858e50, -0.153825e-15, 0.01, 1.0, -1.0, 2.0 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_6r64);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_6r64);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL6r64_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r64_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT8i08()
{
    static const uint16_t ref_serimg_byte_count = 12;
    int err = EXIT_SUCCESS;
    BL8i8_t src0 = { 0x55, 0xfe, 0x31, 0x01, 0x55, 0xfe, 0x31, 0x01 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_8i8);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_8i8);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL8i8_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int8_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT8i16()
{
    static const uint16_t ref_serimg_byte_count = 20;
    int err = EXIT_SUCCESS;
    BL8i16_t src0 = { 0x55fe, 0xfe55, 0x3030, 0x0101, 0x55fe, 0xfe55, 0x3030, 0x0101 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_8i16);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_8i16);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL8i16_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int16_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT8i32()
{
    static const uint16_t ref_serimg_byte_count = 36;
    int err = EXIT_SUCCESS;
    BL8i32_t src0 = { 0xfe5555fe, 0x55fefe55, 0x30300303, 0x01010101, 0xfe5555fe, 0x55fefe55, 0x30300303, 0x01010101 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_8i32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_8i32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL8i32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const int32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT8r32()
{
    static const uint16_t ref_serimg_byte_count = 36;
    int err = EXIT_SUCCESS;
    BL8r32_t src0 = { 1.5858e05f, -0.153825e-5f, 25.0e-3f, 1.0f, 1.5858e05f, -0.153825e-5f, 25.0e-3f, 1.0f };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_8r32);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_8r32);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL8r32_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r32_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UT8r64()
{
    static const uint16_t ref_serimg_byte_count = 68;
    int err = EXIT_SUCCESS;
    BL8r64_t src0 = { 1.5858e50, -0.153825e-15, 0.01, 1.0, 1.5858e50, -0.153825e-15, 0.01, 1.0 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_8r64);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_8r64);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(&src0);
        if (serimg_byte_count != ref_serimg_byte_count)
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const uint8_t*)src0, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != sizeof(BL8r64_t))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (!BLeq2(src0, (const BL1r64_t*)deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UTstri()
{
    int err = EXIT_SUCCESS;
    const char* src_str = "0123ABCDefgh";
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_string);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_string);
    BLserializable_convert_f deserializer = NULL;
    do {
        uint16_t serimg_byte_count = serest(src_str);
        if (serimg_byte_count != (strlen(src_str) + BYTES_4CC + sizeof(uint16_t)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer(src_str, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != (1 + strlen(src_str)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        if (strcmp(deserimg, src_str))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UTai08()
{
    int err = EXIT_SUCCESS;
    const int8_t src_raw_array[] = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_i8array);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_i8array);
    BLserializable_convert_f deserializer = NULL;
    pBLarray1D_t array = NULL;
    BL2u16_t array_size = { 1, ARRAYSIZE(src_raw_array) };
    BLarray1D_alloc(array, array_size);
    memcpy(BLarray1D_begin(array), src_raw_array, sizeof(src_raw_array));
    do {
        uint16_t serimg_byte_count = serest(array);
        if (serimg_byte_count != (BYTES_4CC + sizeof(uint16_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const void*)array, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != (sizeof(BLarray1D_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        const int8_t* i_deser = BLarray1D_begin((pcBLarray1D_t)deserimg);
        for (uint16_t i = 0; i < array->size[1]; i++)
        {
            if (i_deser[i] != src_raw_array[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    BLSAFEFREE(&array);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UTai16()
{
    int err = EXIT_SUCCESS;
    const int16_t src_raw_array[] = { 0x3030, 0x0101, 0x02ff, 0x03cc, 0x04dc };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_i16array);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_i16array);
    BLserializable_convert_f deserializer = NULL;
    pBLarray1D_t array = NULL;
    BL2u16_t array_size = { sizeof(int16_t), ARRAYSIZE(src_raw_array) };
    BLarray1D_alloc(array, array_size);
    memcpy(BLarray1D_begin(array), src_raw_array, sizeof(src_raw_array));
    do {
        uint16_t serimg_byte_count = serest(array);
        if (serimg_byte_count != (BYTES_4CC + sizeof(uint16_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const void*)array, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != (sizeof(BLarray1D_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        const int16_t* i_deser = (const int16_t*)BLarray1D_begin((pcBLarray1D_t)deserimg);
        for (uint16_t i = 0; i < array->size[1]; i++)
        {
            if (i_deser[i] != src_raw_array[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    BLSAFEFREE(&array);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UTai32()
{
    int err = EXIT_SUCCESS;
    const int32_t src_raw_array[] = { 0x30304040, 0x01010202, 0x02ff0000, 0x03ccffff, 0x04dcfeff };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_i32array);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_i32array);
    BLserializable_convert_f deserializer = NULL;
    pBLarray1D_t array = NULL;
    BL2u16_t array_size = { sizeof(int32_t), ARRAYSIZE(src_raw_array) };
    BLarray1D_alloc(array, array_size);
    memcpy(BLarray1D_begin(array), src_raw_array, sizeof(src_raw_array));
    do {
        uint16_t serimg_byte_count = serest(array);
        if (serimg_byte_count != (BYTES_4CC + sizeof(uint16_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const void*)array, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != (sizeof(BLarray1D_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        const int32_t* i_deser = (const int32_t*)BLarray1D_begin((pcBLarray1D_t)deserimg);
        for (uint16_t i = 0; i < array->size[1]; i++)
        {
            if (i_deser[i] != src_raw_array[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    BLSAFEFREE(&array);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UTar32()
{
    int err = EXIT_SUCCESS;
    const BL1r32_t src_raw_array[] = { 1.0f, 1.5f, -2.0f, -2.5f, 0.1f };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_r32array);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_r32array);
    BLserializable_convert_f deserializer = NULL;
    pBLarray1D_t array = NULL;
    BL2u16_t array_size = { sizeof(BL1r32_t), ARRAYSIZE(src_raw_array) };
    BLarray1D_alloc(array, array_size);
    memcpy(BLarray1D_begin(array), src_raw_array, sizeof(src_raw_array));
    do {
        uint16_t serimg_byte_count = serest(array);
        if (serimg_byte_count != (BYTES_4CC + sizeof(uint16_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const void*)array, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != (sizeof(BLarray1D_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        const BL1r32_t* i_deser = (const BL1r32_t*)BLarray1D_begin((pcBLarray1D_t)deserimg);
        for (uint16_t i = 0; i < array->size[1]; i++)
        {
            if (i_deser[i] != src_raw_array[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    BLSAFEFREE(&array);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
static int UTar64()
{
    int err = EXIT_SUCCESS;
    const BL1r64_t src_raw_array[] = { 1.0, 2.0, -1.0, -2.0, 0.1e-22 };
    uint8_t *serimg = NULL, *deserimg = NULL;
    BLserializable_estsize_f serest = BLserializable_serialize_estimator(BLserializable_r64array);
    BLserializable_estsize_f deserest = NULL;
    BLserializable_convert_f serializer = BLserializable_serializer(BLserializable_r64array);
    BLserializable_convert_f deserializer = NULL;
    pBLarray1D_t array = NULL;
    BL2u16_t array_size = { sizeof(BL1r64_t), ARRAYSIZE(src_raw_array) };
    BLarray1D_alloc(array, array_size);
    memcpy(BLarray1D_begin(array), src_raw_array, sizeof(src_raw_array));
    do {
        uint16_t serimg_byte_count = serest(array);
        if (serimg_byte_count != (BYTES_4CC + sizeof(uint16_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        serimg = (uint8_t*)malloc(serimg_byte_count);
        if (EXIT_SUCCESS != serializer((const void*)array, serimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        BLserializable_ID_t restoredID = BLserializable_ID(serimg);
        deserest = BLserializable_deserialize_estimator(restoredID);
        deserializer = BLserializable_deserializer(restoredID);
        uint16_t deserimg_byte_count = deserest(serimg);
        if (deserimg_byte_count != (sizeof(BLarray1D_t) + sizeof(src_raw_array)))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        deserimg = (uint8_t*)malloc(deserimg_byte_count);
        if (EXIT_SUCCESS != deserializer(serimg, deserimg))
        {
            err = EXIT_FAILURE;
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
        const BL1r64_t* i_deser = (const BL1r64_t*)BLarray1D_begin((pcBLarray1D_t)deserimg);
        for (uint16_t i = 0; i < array->size[1]; i++)
        {
            if (i_deser[i] != src_raw_array[i])
            {
                err = EXIT_FAILURE;
                break;
            }
        }
        if (err)
        {
            UT_SHOWBREAK(stderr, __FUNCTION__, __LINE__, err);
        }
    } while (0);
    BLSAFEFREE(&serimg);
    BLSAFEFREE(&deserimg);
    BLSAFEFREE(&array);
    UT_SHOW(stdout, __FUNCTION__, __LINE__, err);
    return err;
}
