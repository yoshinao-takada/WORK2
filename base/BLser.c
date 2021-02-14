#include    "base/BLser.h"
#include    "base/BLsv.h"
#include    "base/BLarray1D.h"
#include    <errno.h>
#include    <memory.h>
#include    <string.h>

static const char* BLserializable_4ccs[] = BLSERIALIZABLE4CC_TABLE;

#pragma region serialized_size_estimators
static uint16_t size_1(const void* src) { return 1 + BYTES_4CC; }
static uint16_t size_2(const void* src) { return 2 + BYTES_4CC; }
static uint16_t size_3(const void* src) { return 3 + BYTES_4CC; }
static uint16_t size_4(const void* src) { return 4 + BYTES_4CC; }
static uint16_t size_6(const void* src) { return 6 + BYTES_4CC; }
static uint16_t size_8(const void* src) { return 8 + BYTES_4CC; }
static uint16_t size_12(const void* src) { return 12 + BYTES_4CC; }
static uint16_t size_16(const void* src) { return 16 + BYTES_4CC; }
static uint16_t size_24(const void* src) { return 24 + BYTES_4CC; }
static uint16_t size_32(const void* src) { return 32 + BYTES_4CC; }
static uint16_t size_48(const void* src) { return 48 + BYTES_4CC; }
static uint16_t size_64(const void* src) { return 64 + BYTES_4CC; }
static uint16_t size_cstr(const void* src) 
{
    return (uint16_t)(strlen((const char*)src) + 2 + BYTES_4CC);
}
static uint16_t size_array1D(const void* src)
{
    pcBLarray1D_t a = (pcBLarray1D_t)src;
    return a->size[0] * a->size[1] + 2 + BYTES_4CC;
}

static BLserializable_estsize_f ser_estimators[] =
{
    size_1, size_2, size_4, size_4, size_8,
    size_2, size_4, size_8, size_8, size_16,
    size_3, size_6, size_12, size_12, size_24,
    size_4, size_8, size_16, size_16, size_32,
    size_6, size_12, size_24, size_24, size_48,
    size_8, size_16, size_32, size_32, size_64,
    size_cstr,
    size_array1D, size_array1D, size_array1D, size_array1D, size_array1D
};
#pragma endregion serialized_size_estimators

#pragma region deserialized_size_estimators
static uint16_t desize_1(const void* src) { return 1; }
static uint16_t desize_2(const void* src) { return 2; }
static uint16_t desize_3(const void* src) { return 3; }
static uint16_t desize_4(const void* src) { return 4; }
static uint16_t desize_6(const void* src) { return 6; }
static uint16_t desize_8(const void* src) { return 8; }
static uint16_t desize_12(const void* src) { return 12; }
static uint16_t desize_16(const void* src) { return 16; }
static uint16_t desize_24(const void* src) { return 24; }
static uint16_t desize_32(const void* src) { return 32; }
static uint16_t desize_48(const void* src) { return 48; }
static uint16_t desize_64(const void* src) { return 64; }
static uint16_t desize_cstr(const void* src)
{
    const uint16_t* payload_size = (const uint16_t*)(((const uint8_t*)src) + BYTES_4CC);
    return *payload_size + 1;
}
static uint16_t desize_array1Di8(const void* src)
{
    const uint16_t* payload_size = (const uint16_t*)(((const uint8_t*)src) + BYTES_4CC);
    return sizeof(BLarray1D_t) + *payload_size;
}
static uint16_t desize_array1Di16(const void* src)
{
    const uint16_t* payload_size = (const uint16_t*)(((const uint8_t*)src) + BYTES_4CC);
    return sizeof(BLarray1D_t) + (*payload_size) * sizeof(int16_t);
}
static uint16_t desize_array1Di32(const void* src)
{
    const uint16_t* payload_size = (const uint16_t*)(((const uint8_t*)src) + BYTES_4CC);
    return sizeof(BLarray1D_t) + (*payload_size) * sizeof(int32_t);
}
static uint16_t desize_array1Dr64(const void* src)
{
    const uint16_t* payload_size = (const uint16_t*)(((const uint8_t*)src) + BYTES_4CC);
    return sizeof(BLarray1D_t) + (*payload_size) * sizeof(BL1r64_t);
}

static BLserializable_estsize_f deser_estimators[] =
{
    desize_1, desize_2, desize_4, desize_4, desize_8,
    desize_2, desize_4, desize_8, desize_8, desize_16,
    desize_3, desize_6, desize_12, desize_12, desize_24,
    desize_4, desize_8, desize_16, desize_16, desize_32,
    desize_6, desize_12, desize_24, desize_24, desize_48,
    desize_8, desize_16, desize_32, desize_32, desize_64,
    desize_cstr,
    desize_array1Di8, desize_array1Di16, desize_array1Di32, desize_array1Di32, desize_array1Dr64
};
#pragma endregion deserialized_size_estimators

#pragma region serializers
static int ser1i8(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_1i8);
    *(dst + BYTES_4CC) = *src;
    return 0;
}
static int ser1i16(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_1i16);
    *(BL1i16_t*)(dst + BYTES_4CC) = *(const BL1i16_t*)src;
    return 0;
}
static int ser1i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_1i32);
    *(BL1i32_t*)(dst + BYTES_4CC) = *(const BL1i32_t*)src;
    return 0;
}
static int ser1r32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_1r32);
    *(BL1r32_t*)(dst + BYTES_4CC) = *(const BL1r32_t*)src;
    return 0;
}
static int ser1r64(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_1r64);
    memcpy(dst + BYTES_4CC, src, sizeof(BL1r64_t));
    return 0;
}
static int ser2i8(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_2i8);
    memcpy(dst + BYTES_4CC, src, sizeof(BL2i8_t));
    return 0;
}
static int ser2i16(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_2i16);
    memcpy(dst + BYTES_4CC, src, sizeof(BL2i16_t));
    return 0;
}
static int ser2i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_2i32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL2i32_t));
    return 0;
}
static int ser2r32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_2r32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL2r32_t));
    return 0;
}
static int ser2r64(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_2r64);
    memcpy(dst + BYTES_4CC, src, sizeof(BL2r64_t));
    return 0;
}
static int ser3i8(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_3i8);
    memcpy(dst + BYTES_4CC, src, sizeof(BL3i8_t));
    return 0;
}
static int ser3i16(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_3i16);
    memcpy(dst + BYTES_4CC, src, sizeof(BL3i16_t));
    return 0;
}
static int ser3i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_3i32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL3i32_t));
    return 0;
}
static int ser3r32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_3r32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL3r32_t));
    return 0;
}
static int ser3r64(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_3r64);
    memcpy(dst + BYTES_4CC, src, sizeof(BL3r64_t));
    return 0;
}
static int ser4i8(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_4i8);
    memcpy(dst + BYTES_4CC, src, sizeof(BL4i8_t));
    return 0;
}
static int ser4i16(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_4i16);
    memcpy(dst + BYTES_4CC, src, sizeof(BL4i16_t));
    return 0;
}
static int ser4i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_4i32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL4i32_t));
    return 0;
}
static int ser4r32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_4r32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL4r32_t));
    return 0;
}
static int ser4r64(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_4r64);
    memcpy(dst + BYTES_4CC, src, sizeof(BL4r64_t));
    return 0;
}
static int ser6i8(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_6i8);
    memcpy(dst + BYTES_4CC, src, sizeof(BL6i8_t));
    return 0;
}
static int ser6i16(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_6i16);
    memcpy(dst + BYTES_4CC, src, sizeof(BL6i16_t));
    return 0;
}
static int ser6i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_6i32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL6i32_t));
    return 0;
}
static int ser6r32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_6r32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL6r32_t));
    return 0;
}
static int ser6r64(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_6r64);
    memcpy(dst + BYTES_4CC, src, sizeof(BL6r64_t));
    return 0;
}
static int ser8i8(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_8i8);
    memcpy(dst + BYTES_4CC, src, sizeof(BL8i8_t));
    return 0;
}
static int ser8i16(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_8i16);
    memcpy(dst + BYTES_4CC, src, sizeof(BL8i16_t));
    return 0;
}
static int ser8i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_8i32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL8i32_t));
    return 0;
}
static int ser8r32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_8r32);
    memcpy(dst + BYTES_4CC, src, sizeof(BL8r32_t));
    return 0;
}
static int ser8r64(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_8r64);
    memcpy(dst + BYTES_4CC, src, sizeof(BL8r64_t));
    return 0;
}
static int ser_cstr(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = BLserializable_4cci32(BLserializable_string);
    size_t copylen = (size_t)(*(uint16_t*)(dst + BYTES_4CC) = (uint16_t)strlen(src));
    if (copylen <= BLSERIALIZABLE_STRLEN_MAX)
    {
        memcpy(dst + BYTES_4CC + sizeof(uint16_t), src, copylen);
        return EXIT_SUCCESS;
    }
    else
    {
        return EINVAL;
    }
}
static int ser_array(int32_t i32cc4, const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = i32cc4;
    pcBLarray1D_t src_array = (pcBLarray1D_t)src;
    int err = EXIT_SUCCESS;
    do {
        size_t dst_len = src_array->size[0] * src_array->size[1];
        if (dst_len > BLSERIALIZABLE_DATALEN_MAX)
        {
            err = EINVAL;
            break;
        }
        *(uint16_t*)(dst + BYTES_4CC) = src_array->size[1];
        memcpy(dst + BYTES_4CC + BYTES_SIZE, BLarray1D_begin(src_array), dst_len);
    } while (0);
    return err;
}

static int ser_ai8(const uint8_t* src, uint8_t* dst)
{
    return ser_array(BLserializable_4cci32(BLserializable_i8array), src, dst);
}
static int ser_ai16(const uint8_t* src, uint8_t* dst)
{
    return ser_array(BLserializable_4cci32(BLserializable_i16array), src, dst);
}
static int ser_ai32(const uint8_t* src, uint8_t* dst)
{
    return ser_array(BLserializable_4cci32(BLserializable_i32array), src, dst);
}
static int ser_ar32(const uint8_t* src, uint8_t* dst)
{
    return ser_array(BLserializable_4cci32(BLserializable_r32array), src, dst);
}
static int ser_ar64(const uint8_t* src, uint8_t* dst)
{
    return ser_array(BLserializable_4cci32(BLserializable_r64array), src, dst);
}

static BLserializable_convert_f serializers[] = 
{
    ser1i8, ser1i16, ser1i32, ser1r32, ser1r64,
    ser2i8, ser2i16, ser2i32, ser2r32, ser2r64,
    ser3i8, ser3i16, ser3i32, ser3r32, ser3r64,
    ser4i8, ser4i16, ser4i32, ser4r32, ser4r64,
    ser6i8, ser6i16, ser6i32, ser6r32, ser6r64,
    ser8i8, ser8i16, ser8i32, ser8r32, ser8r64,
    ser_cstr,
    ser_ai8, ser_ai16, ser_ai32, ser_ar32, ser_ar64
};
#pragma endregion serializers

#pragma region deserializers
static int deser1i8(const uint8_t* src, uint8_t* dst)
{
    *dst = *(src + BYTES_4CC);
    return 0;
}
static int deser1i16(const uint8_t* src, uint8_t* dst)
{
    *(int16_t*)dst = *(const int16_t*)(src + BYTES_4CC);
    return 0;
}
static int deser1i32(const uint8_t* src, uint8_t* dst)
{
    *(int32_t*)dst = *(const int32_t*)(src + BYTES_4CC);
    return 0;
}
static int deser1r32(const uint8_t* src, uint8_t* dst)
{
    *(BL1r32_t*)dst = *(const BL1r32_t*)(src + BYTES_4CC);
    return 0;
}
static int deser1r64(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, src + BYTES_4CC, sizeof(BL1r64_t));
    return 0;
}
static int deser2i8(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL2i8_t));
    return 0;
}
static int deser2i16(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL2i16_t));
    return 0;
}
static int deser2i32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL2i32_t));
    return 0;
}
static int deser2r32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL2r32_t));
    return 0;
}
static int deser2r64(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL2r64_t));
    return 0;
}
static int deser3i8(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL3i8_t));
    return 0;
}
static int deser3i16(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL3i16_t));
    return 0;
}
static int deser3i32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL3i32_t));
    return 0;
}
static int deser3r32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL3r32_t));
    return 0;
}
static int deser3r64(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL3r64_t));
    return 0;
}
static int deser4i8(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL4i8_t));
    return 0;
}
static int deser4i16(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL4i16_t));
    return 0;
}
static int deser4i32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL4i32_t));
    return 0;
}
static int deser4r32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL4r32_t));
    return 0;
}
static int deser4r64(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL4r64_t));
    return 0;
}
static int deser6i8(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL6i8_t));
    return 0;
}
static int deser6i16(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL6i16_t));
    return 0;
}
static int deser6i32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL6i32_t));
    return 0;
}
static int deser6r32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL6r32_t));
    return 0;
}
static int deser6r64(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL6r64_t));
    return 0;
}
static int deser8i8(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL8i8_t));
    return 0;
}
static int deser8i16(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL8i16_t));
    return 0;
}
static int deser8i32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL8i32_t));
    return 0;
}
static int deser8r32(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL8r32_t));
    return 0;
}
static int deser8r64(const uint8_t* src, uint8_t* dst)
{
    memcpy(dst, (src + BYTES_4CC), sizeof(BL8r64_t));
    return 0;
}
static int deser_cstr(const uint8_t *src, uint8_t* dst)
{
    int err = EXIT_SUCCESS;
    uint16_t src_len = *(const uint16_t*)(src + BYTES_4CC);
    if (src_len > BLSERIALIZABLE_STRLEN_MAX)
    {
        return EINVAL;
    }
    memcpy(dst, src + BYTES_4CC + BYTES_SIZE, src_len);
    *(dst + (ptrdiff_t)src_len) = '\0';
    return EXIT_SUCCESS;
}
static int deser_array(BLserializable_ID_t id, const uint8_t *src, uint8_t* dst)
{
    static const uint16_t element_byte_counts[] = { 1, 2, 4, 4, 8 };
    int index = (int)id - BLserializable_i8array;
    if ((index < 0) || (5 <= index))
    {
        return EINVAL;
    }
    pBLarray1D_t array = (pBLarray1D_t)dst;
    array->size[0] = element_byte_counts[index];
    array->size[1] = *(const uint16_t*)(src + BYTES_4CC);
    memcpy(BLarray1D_begin(array), src + BYTES_4CC + BYTES_SIZE, array->size[0] * array->size[1]);
    return EXIT_SUCCESS;
}
static int deser_ai8(const uint8_t* src, uint8_t* dst)
{
    return deser_array(BLserializable_i8array, src, dst);
}
static int deser_ai16(const uint8_t* src, uint8_t* dst)
{
    return deser_array(BLserializable_i16array, src, dst);
}
static int deser_ai32(const uint8_t* src, uint8_t* dst)
{
    return deser_array(BLserializable_i32array, src, dst);
}
static int deser_ar32(const uint8_t* src, uint8_t* dst)
{
    return deser_array(BLserializable_r32array, src, dst);
}
static int deser_ar64(const uint8_t* src, uint8_t* dst)
{
    return deser_array(BLserializable_r64array, src, dst);
}
static BLserializable_convert_f deserializers[] = 
{
    deser1i8, deser1i16, deser1i32, deser1r32, deser1r64,
    deser2i8, deser2i16, deser2i32, deser2r32, deser2r64,
    deser3i8, deser3i16, deser3i32, deser3r32, deser3r64,
    deser4i8, deser4i16, deser4i32, deser4r32, deser4r64,
    deser6i8, deser6i16, deser6i32, deser6r32, deser6r64,
    deser8i8, deser8i16, deser8i32, deser8r32, deser8r64,
    deser_cstr,
    deser_ai8, deser_ai16, deser_ai32, deser_ar32, deser_ar64,
};
#pragma endregion deserializers

#pragma region table_accessors
const char* BLserializable_4cc(BLserializable_ID_t id)
{
    return BLserializable_4ccs[id];
}

int32_t     BLserializable_4cci32(BLserializable_ID_t id)
{
    return *(const int32_t*)BLserializable_4cc(id);
}

BLserializable_ID_t BLserializable_ID(const uint8_t* _4cc)
{
    BLserializable_ID_t id = (BLserializable_ID_t)(-1);
    for (int i = 0; i < sizeof(BLserializable_4ccs); i++)
    {
        if (BLeq4(_4cc, BLserializable_4ccs[i]))
        {
            id = (BLserializable_ID_t)i;
            break;
        }
    }
    return id;
}

BLserializable_estsize_f BLserializable_serialize_estimator(BLserializable_ID_t id)
{
    return ser_estimators[id];
}

/*!
\brief get a size estimator for deserialized image
*/
BLserializable_estsize_f BLserializable_deserialize_estimator(BLserializable_ID_t id)
{
    return deser_estimators[id];
}

/*!
\brief get a serializer
*/
BLserializable_convert_f BLserializable_serializer(BLserializable_ID_t id)
{
    return serializers[id];
}

/*!
\brief get a deserializer
*/
BLserializable_convert_f BLserializable_deserializer(BLserializable_ID_t id)
{
    return deserializers[id];
}
#pragma endregion table_accessors

