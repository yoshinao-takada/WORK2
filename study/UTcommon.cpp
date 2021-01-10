#include    "study/UTcommon.h"
#include    "base/BLfile.h"
#include    <errno.h>
#include    <opencv2/core.hpp>
#include    <opencv2/imgproc.hpp>
#include    <opencv2/imgcodecs.hpp>

static uint32_t element_size[] = BLimage_element_size;

static int BLcommon_create_parent_directory(const char* filepath)
{
    int err = EXIT_SUCCESS;
    do {
        char* dirpath = (char*)alloca(strlen(filepath)+1);
        memcpy(dirpath, filepath, strlen(filepath));
        char* scanner = dirpath + strlen(dirpath)-1;
        for (; scanner != dirpath; scanner--)
        {
            if (*scanner == '/') break;
        }
        if (*scanner == '/')
        {
            *scanner = '\0';
            err = BLfile_create_directories(dirpath);
        }
        else
        {
            err = EINVAL;
        }
    } while (0);
    return err;
}
static int BLcommon_save_image_grayscale(const char* filepath, pBLarray_t array)
{
    char* buf = NULL;
    int err = EXIT_SUCCESS;
    do {
        if (array->size[0] != 1)
        {
            err = EINVAL;
            break;
        }
        cv::Mat1b cvmat((int)array->size[2], (int)array->size[1], (uchar*)BLarray_begin(array));
        cv::imwrite(filepath, cvmat);
    } while (0);
    return err;
}

static int BLcommon_save_image_csv_map2D(const char* filepath, pBLarray_t array, BLimage_save_type_t save_type)
{
    int err = EXIT_SUCCESS;
    FILE* pf = NULL;
    do {
        if (EXIT_SUCCESS != (err = BLfile_open(&pf, filepath, "w")))
        {
            break;
        }
        fprintf(pf, "iy");
        for (uint32_t ix = 0; ix != array->size[1]; ix++)
        {
            fprintf(pf, ",e(%d:iy)", ix);
        }
        fprintf(pf, "\n");
        const BL1i8_t* i_array_i8 = (const BL1i8_t*)BLarray_begin(array);
        const BL1u8_t* i_array_u8 = (const BL1u8_t*)BLarray_begin(array);
        const BL1i16_t* i_array_i16 = (const BL1i16_t*)BLarray_begin(array);
        const BL1u16_t* i_array_u16 = (const BL1u16_t*)BLarray_begin(array);
        const BL1i32_t* i_array_i32 = (const BL1i32_t*)BLarray_begin(array);
        const BL1u32_t* i_array_u32 = (const BL1u32_t*)BLarray_begin(array);
        const BL1r32_t* i_array_r32 = (const BL1r32_t*)BLarray_begin(array);

        for (uint32_t iy = 0; iy != array->size[2]; iy++)
        {
            fprintf(pf, "%d", iy);
            for (uint32_t ix = 0; ix != array->size[1]; ix++)
            {
                switch (save_type)
                {
                    case BLimage_save_type_csv_map2D_1i8:
                        fprintf(pf, ",%d", i_array_i8[ix]);
                        break;
                    case BLimage_save_type_csv_map2D_1u8:
                        fprintf(pf, ",%d", i_array_u8[ix]);
                        break;
                    case BLimage_save_type_csv_map2D_1i16:
                        fprintf(pf, ",%d", i_array_i16[ix]);
                        break;
                    case BLimage_save_type_csv_map2D_1u16:
                        fprintf(pf, ",%d", i_array_u16[ix]);
                        break;
                    case BLimage_save_type_csv_map2D_1i32:
                        fprintf(pf, ",%d", i_array_i32[ix]);
                        break;
                    case BLimage_save_type_csv_map2D_1u32:
                        fprintf(pf, ",%d", i_array_u32[ix]);
                        break;
                    case BLimage_save_type_csv_map2D_1r32:
                        fprintf(pf, ",%f", i_array_r32[ix]);
                        break;
                }
            }
            i_array_i8 += array->size[1];
            i_array_u8 += array->size[1];
            i_array_i16 += array->size[1];
            i_array_u16 += array->size[1];
            i_array_i32 += array->size[1];
            i_array_u32 += array->size[1];
            i_array_r32 += array->size[1];
            fprintf(pf, "\n");
        }
    } while (0);
    if (pf) fclose(pf);
    return err;
}

static int BLcommon_save_image_csv_column(const char* filepath, pBLarray_t array, BLimage_save_type_t save_type)
{
    int err = EXIT_SUCCESS;
    FILE* pf = NULL;
    do {
        if (EXIT_SUCCESS != (err = BLfile_open(&pf, filepath, "w")))
        {
            break;
        }
        fprintf(pf, "ix,iy,e(ix,iy)\n");
        const BL1i8_t* i_array_i8 = (const BL1i8_t*)BLarray_begin(array);
        const BL1u8_t* i_array_u8 = (const BL1u8_t*)BLarray_begin(array);
        const BL1i16_t* i_array_i16 = (const BL1i16_t*)BLarray_begin(array);
        const BL1u16_t* i_array_u16 = (const BL1u16_t*)BLarray_begin(array);
        const BL1i32_t* i_array_i32 = (const BL1i32_t*)BLarray_begin(array);
        const BL1u32_t* i_array_u32 = (const BL1u32_t*)BLarray_begin(array);
        const BL1r32_t* i_array_r32 = (const BL1r32_t*)BLarray_begin(array);
        for (uint32_t iy = 0; iy != array->size[2]; iy++)
        {
            for (uint32_t ix = 0; ix != array->size[1]; ix++)
            {
                fprintf(pf, "%d,%d,", ix, iy);
                switch (save_type)
                {
                    case BLimage_save_type_csv_column_1i8:
                        fprintf(pf, "%d", i_array_i8[ix]);
                        break;
                    case BLimage_save_type_csv_column_1u8:
                        fprintf(pf, "%d", i_array_u8[ix]);
                        break;
                    case BLimage_save_type_csv_column_1i16:
                        fprintf(pf, "%d", i_array_i16[ix]);
                        break;
                    case BLimage_save_type_csv_column_1u16:
                        fprintf(pf, "%d", i_array_u16[ix]);
                        break;
                    case BLimage_save_type_csv_column_1i32:
                        fprintf(pf, "%d", i_array_i32[ix]);
                        break;
                    case BLimage_save_type_csv_column_1u32:
                        fprintf(pf, "%d", i_array_u32[ix]);
                        break;
                    case BLimage_save_type_csv_column_1r32:
                        fprintf(pf, "%f", i_array_r32[ix]);
                        break;
                }
                fprintf(pf, "\n");
            }
            i_array_i8 += array->size[1];
            i_array_u8 += array->size[1];
            i_array_i16 += array->size[1];
            i_array_u16 += array->size[1];
            i_array_i32 += array->size[1];
            i_array_u32 += array->size[1];
            i_array_r32 += array->size[1];
        }
    } while (0);
    return err;
}
int BLcommon_save_image(const char* filepath, pBLarray_t array, BLimage_save_type_t save_type)
{
    int err = EXIT_SUCCESS;
    do {
        if (EXIT_SUCCESS != (err = BLcommon_create_parent_directory(filepath)))
        {
            break;
        }
        if (element_size[(int)save_type] != array->size[0])
        {
            err = EINVAL;
            break;
        }
        switch (save_type)
        {
            case BLimage_save_type_grayscale:
            {
                err = BLcommon_save_image_grayscale(filepath, array);
                break;
            }
            case BLimage_save_type_BGR24:
            {

            }
            case BLimage_save_type_csv_map2D_1u8:
            case BLimage_save_type_csv_map2D_1i8:
            case BLimage_save_type_csv_map2D_1u16:
            case BLimage_save_type_csv_map2D_1i16:
            case BLimage_save_type_csv_map2D_1u32:
            case BLimage_save_type_csv_map2D_1i32:
            case BLimage_save_type_csv_map2D_1r32:
            {
                err = BLcommon_save_image_csv_map2D(filepath, array, save_type);
                break;
            }
            case BLimage_save_type_csv_column_1i8:
            case BLimage_save_type_csv_column_1u8:
            case BLimage_save_type_csv_column_1i16:
            case BLimage_save_type_csv_column_1u16:
            case BLimage_save_type_csv_column_1i32:
            case BLimage_save_type_csv_column_1u32:
            case BLimage_save_type_csv_column_1r32:
            {
                err = BLcommon_save_image_csv_column(filepath, array, save_type);
                break;
            }
        }
    } while (0);
    return err;
}

int BLcommon_randimg(pBLarray_t img)
{
    srand(0);
    int err = EXIT_SUCCESS;
    pBLarray_t shrinked_img = NULL;
    do {
        BL4u32_t shrinked_size = BLarray_size2D(BL1u8_t, img->size[1]/10 + 1, img->size[2]/10 + 1);
        BLarray_alloc(shrinked_img, shrinked_size);
        BL1u8_t* p = BLarray_begin(shrinked_img);
        uint32_t shrinked_area = BLprod4(shrinked_size);
        do {
            *p++ = (uint8_t)(rand() % 128);
        } while (--shrinked_area);

        BL2u32_t index;
        for (index[1] = 0; index[1] != img->size[2]; index[1]++)
        {
            for (index[0] = 0; index[0] != img->size[1]; index[0]++)
            {
                BL2u32_t shrinked_index = { index[0]/10, index[1]/10 };
                uint8_t val = *(BLarray_at2D(shrinked_img, shrinked_index)) + (uint8_t)(rand() % 128);
                *BLarray_at2D(img, index) = val;
            }
        }
    } while (0);
    BLSAFEFREE(&shrinked_img);
    return err;
}