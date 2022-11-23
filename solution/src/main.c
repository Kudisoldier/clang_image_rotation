#include "bmp.h"
#include "image.h"
#include "io.h"
#include "rotate.h"

int main( int argc, char** argv ) {    
    if (argc != 3) print_err("Usage: ./image-transformer <source-image> <transformed-image>");

    FILE* source_file = file_open_rb(argv[1]);
    struct bmp_image source_bmp = read_bmp(source_file);
    file_close(source_file);
    
    struct image source_image = convert_bmp_to_image(source_bmp);

    struct image transformed_image = image_rotate_90deg_counterclokwise(source_image);
    free(source_image.data);

    struct bmp_image transformed_bmp = convert_image_to_bmp(transformed_image);

    FILE* transformed_file = file_open_wb(argv[2]);
    write_bmp(transformed_file, transformed_bmp);
    file_close(transformed_file);
    free(transformed_image.data);

    return 0;
}
