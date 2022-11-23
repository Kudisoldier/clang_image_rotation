#pragma once

#include <stdint.h>
#include <stdlib.h>

#include "pixel.h"

struct image {
  uint64_t width, height;
  struct pixel* data;
};

struct image create_image(uint64_t width, uint64_t height);
