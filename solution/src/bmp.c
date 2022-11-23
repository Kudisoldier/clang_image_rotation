#include "bmp.h"

static bool verify_bmp_header(struct bmp_header header) {
    if (header.biBitCount == 24 && header.bfType == 19778 &&
    header.bOffBits == 54 && header.biSize == 40) return true;
    else return false;
}

static uint8_t get_padding(uint64_t width) {
    return width % 4;
}

struct bmp_image read_bmp(FILE* fp) {
    struct bmp_image bmp = {{0}};
    if(!fread(&bmp.header, sizeof(struct bmp_header), 1, fp)) print_err("Cannot read header of bmp");

    if (!verify_bmp_header(bmp.header)) print_err("Corrupted bmp header");

    uint8_t padding = get_padding(bmp.header.biWidth);
    size_t row_count;
    bmp.pixels = malloc(sizeof(struct pixel)*bmp.header.biHeight*bmp.header.biWidth);

    for (size_t row=0; row < bmp.header.biHeight; row++) {
        row_count = fread(&(bmp.pixels[row*bmp.header.biWidth]), sizeof(struct pixel), bmp.header.biWidth, fp);
        int64_t fseek_result = fseek(fp, padding, SEEK_CUR);
        if (bmp.header.biWidth != row_count || fseek_result != 0) print_err("Cannot read contents of bmp");
    }
    
    return bmp;
}

struct image convert_bmp_to_image(struct bmp_image bmp) {
    struct image converted = {
        .width = bmp.header.biWidth,
        .height = bmp.header.biHeight,
        .data = bmp.pixels
    };

    return converted;
}

static struct bmp_header generate_bmp_header(uint64_t width, uint64_t height) {
    uint32_t biSizeImage = width * height * sizeof(struct pixel) + height * get_padding(width);
    uint32_t biFileSize = sizeof(struct bmp_header) + biSizeImage;
    

    struct bmp_header generated_bmp_header = {
        19778, biFileSize, 0, sizeof(struct bmp_header), 40, width, height, 1, 24, 0, biSizeImage, 0, 0, 0, 0
    };

    return generated_bmp_header;
}

struct bmp_image convert_image_to_bmp(struct image image_to_convert) {
    struct bmp_header generated_bmp_header = generate_bmp_header(image_to_convert.width, image_to_convert.height);

    struct bmp_image converted = {.header=generated_bmp_header, .pixels=image_to_convert.data};

    return converted;
}

void write_bmp(FILE* fp, struct bmp_image bmp) {
    if(!fwrite(&bmp.header, sizeof(struct bmp_header), 1, fp)) print_err("Cannot write header of bmp\n");
    uint8_t padding = get_padding(bmp.header.biWidth);

    size_t row_count;
    const uint64_t zero = 0;
    for (size_t row=0; row < bmp.header.biHeight; row++) {
        row_count = fwrite(&(bmp.pixels[row*bmp.header.biWidth]), sizeof(struct pixel), bmp.header.biWidth, fp);
        size_t zeros_count = fwrite(&zero, 1, padding, fp);
        if (zeros_count != padding && bmp.header.biWidth != row_count) print_err("Cannot write contents of bmp\n");
    }
}
