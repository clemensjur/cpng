#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "png.h"

int main(int argc, char **argv) {
  size_t filesize;
  PngFile *file = png_readfile(fopen("assets/img.png", "rb"));
  png_read_chunks(file);
  png_free(file);

  return 0;
}
