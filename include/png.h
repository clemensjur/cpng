#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define PNG_HEADER_VALUE 0x0A1A0A0D474E5089

struct PngHeader {
  uint64_t value;
  bool verified;
} typedef PngHeader;

struct PngChunk {
  uint32_t length;
  char type[4];
  uint8_t *data_ptr;
  uint32_t crc;
  struct PngChunk *next;
} typedef PngChunk;

struct PngFile {
  uint8_t *ptr;
  PngHeader *header;
  size_t filesize;
  uint8_t *chunk_ptr;
  uint32_t num_chunks;
  PngChunk *chunks[];
} typedef PngFile;

PngFile *png_readfile(FILE *in);
void png_read_chunks(PngFile *file);
bool png_verify(PngFile *file);
void png_free(PngFile *file);
