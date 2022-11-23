#include "rotate.h"

struct image image_rotate_90deg_counterclokwise(const struct image source_image) {
    struct image rotated = create_image(source_image.height, source_image.width);
    for (size_t i = 0; i < rotated.height; i++) {
        for (size_t j = 0; j < rotated.width; j++) {
            rotated.data[i*rotated.width+j] = source_image.data[(rotated.width-j-1)*source_image.width+i];
        }
    }
    return rotated;
}
