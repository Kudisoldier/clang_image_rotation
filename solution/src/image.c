#include "image.h"

struct image create_image(uint64_t width, uint64_t height) {
    struct image created = {
        .width = width,
        .height = height,
        .data = malloc(width*height*sizeof(struct pixel))
    };

    return created;
}
