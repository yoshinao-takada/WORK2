#ifndef UTCOMMON_H_
#define UTCOMMON_H_
#include    "base/BLarray.h"

#define WORK_DIR    WORK_DATA "study/"
#define DATA_DIR    TEST_DATA "study/"

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
    BLimage_save_type_grayscale,
    BLimage_save_type_BGR24,
    BLimage_save_type_csv_map2D_1i8,
    BLimage_save_type_csv_map2D_1u8,
    BLimage_save_type_csv_map2D_1i16,
    BLimage_save_type_csv_map2D_1u16,
    BLimage_save_type_csv_map2D_1i32,
    BLimage_save_type_csv_map2D_1u32,
    BLimage_save_type_csv_map2D_1r32,
    BLimage_save_type_csv_column_1i8,
    BLimage_save_type_csv_column_1u8,
    BLimage_save_type_csv_column_1i16,
    BLimage_save_type_csv_column_1u16,
    BLimage_save_type_csv_column_1i32,
    BLimage_save_type_csv_column_1u32,
    BLimage_save_type_csv_column_1r32,
} BLimage_save_type_t;

#define BLimage_element_size    { \
    1, 3, \
    1, 1, 2, 2, 4, 4, 4, \
    1, 1, 2, 2, 4, 4, 4 \
}
int BLcommon_save_image(const char* filepath, pBLarray_t array, BLimage_save_type_t save_type);

int BLcommon_randimg(pBLarray_t img);
#ifdef __cplusplus
}
#endif
#endif /* UTCOMMON_H_ */