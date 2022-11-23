#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "image.h"
#include "io.h"
#include "pixel.h"

struct __attribute__((packed)) bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct bmp_image {
        struct bmp_header header;
        struct pixel* pixels;
};

struct bmp_image read_bmp(FILE* fp);
struct image convert_bmp_to_image(struct bmp_image bmp);
struct bmp_image convert_image_to_bmp(struct image image_to_convert);
void write_bmp(FILE* fp, struct bmp_image bmp);
