#ifndef BLBASE_SER_H_
#define BLBASE_SER_H_
#include    "comm/BLser_ID.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    BLSERIALIZABLE_ID
} BLserializable_ID_t;

#define BLSERIALIZABLE4CC_TABLE { BLSERIALIZABLE4CC }

#define BYTES_4CC   4
#define BYTES_SIZE 2
#define BYTES_EDC   2
#define BYTES_ATTRIB    (BYTES_4CC + BYTES_SIZE + BYTES_EDC)
#define BLSERIALIZABLE_STRLEN_MAX   128
#define PAYLOAD_BYTES_MAX           256
#define BLSERIALIZABLE_DATALEN_MAX  (PAYLOAD_BYTES_MAX - BYTES_ATTRIB)
/*!
\brief byte count estimator of serialized image
\param typeID [in] (int) casted type ID of a serializable data type
\param src [in] source data pointer which can be NULL for fixed size type like BL2r32_t
*/
typedef uint16_t (*BLserializable_estsize_f)(const void* src);

/*!
\brief serializer/deserializer
\param src [in] source data pointer
\param dst [out] destination data buffer
\return unix errno compatible code
*/
typedef int (*BLserializable_convert_f)(const uint8_t* src, uint8_t* dst);

/*!
\brief get a 4cc code
*/
const char* BLserializable_4cc(BLserializable_ID_t id);
int32_t     BLserializable_4cci32(BLserializable_ID_t id);

/*!
\brief get a size estimator for serialized image
*/
BLserializable_estsize_f BLserializable_serialize_estimator(BLserializable_ID_t id);

/*!
\brief get a size estimator for deserialized image
*/
BLserializable_estsize_f BLserializable_deserialize_estimator(BLserializable_ID_t id);

/*!
\brief get a serializer
*/
BLserializable_convert_f BLserializable_serializer(BLserializable_ID_t id);

/*!
\brief get a deserializer
*/
BLserializable_convert_f BLserializable_deserializer(BLserializable_ID_t id);
#ifdef __cplusplus
}
#endif
#endif /* BLBASE_SER_H_ */