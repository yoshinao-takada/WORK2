#ifndef BLSER_ID_H_
#define BLSER_ID_H_
#include    "base/BLbase.h"
/*!
\file BLser_ID.h
\brief Basic symbol definitions of a simple serializer for short vectors.
The basic symbol definitions consists of 
1) serializable data type ID,
2) 4CC codes,

The serializer is allowed to extend to serialize any types of binary data.
A serialized image consists of
1) 4CC code (four ASCII character code similar to 4cc),
2) raw data
*/
#ifdef __cplusplus
extern "C" {
#endif
#define BLSERIALIZABLE_ID \
    BLserializable_1i8, BLserializable_1i16, BLserializable_1i32, BLserializable_1r32, BLserializable_1r64, \
    BLserializable_2i8, BLserializable_2i16, BLserializable_2i32, BLserializable_2r32, BLserializable_2r64, \
    BLserializable_3i8, BLserializable_3i16, BLserializable_3i32, BLserializable_3r32, BLserializable_3r64, \
    BLserializable_4i8, BLserializable_4i16, BLserializable_4i32, BLserializable_4r32, BLserializable_4r64, \
    BLserializable_6i8, BLserializable_6i16, BLserializable_6i32, BLserializable_6r32, BLserializable_6r64, \
    BLserializable_8i8, BLserializable_8i16, BLserializable_8i32, BLserializable_8r32, BLserializable_8r64, \
    BLserializable_string, \
    BLserializable_i8array, BLserializable_i16array, BLserializable_i32array, \
    BLserializable_r32array, BLserializable_r64array,

#define BLSERIALIZABLE4CC \
    "1I08", "1I16", "1I32", "1R32", "1R64", \
    "2I08", "2I16", "2I32", "2R32", "2R64", \
    "3I08", "3I16", "3I32", "3R32", "3R64", \
    "4I08", "4I16", "4I32", "4R32", "4R64", \
    "6I08", "6I16", "6I32", "6R32", "6R64", \
    "8I08", "8I16", "8I32", "8R32", "8R64", \
    "STRI", \
    "AI08", "AI16", "AI32", "AR32", "AR64"

#ifdef __cplusplus
}
#endif
#endif /* BLBSER_ID_H_ */