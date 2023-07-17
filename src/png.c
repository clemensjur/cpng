#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "png.h"

PngFile *png_readfile(FILE *in) {
  fseek(in, 0, SEEK_END);
  long size = ftell(in);
  fseek(in, 0, SEEK_SET); /* same as rewind(f); */

  uint8_t *bytes = malloc(size);
  fread(bytes, size, 1, in);
  fclose(in);

  PngFile *file = malloc(sizeof(PngFile));
  PngHeader *header = malloc(sizeof(PngHeader));
  file->ptr = bytes;
  file->chunk_ptr = file->ptr + 8 * sizeof(uint8_t);
  file->filesize = size;
  file->header = header;
  png_verify(file);

  return file;
}

void png_read_chunks(PngFile *file) {
  size_t chunk_idx = 0;
  uint8_t *chunk_data_ptr = file->chunk_ptr;
  while (true) {
    PngChunk *chunk = malloc(sizeof(PngChunk));
    chunk->data_ptr = chunk_data_ptr;

    memcpy(&chunk->length, chunk->data_ptr, 4 * sizeof(uint8_t));
    uint32_t chunk_size = 12 * sizeof(uint8_t) + chunk->length;
    printf("Chunk length: %d bytes\n", chunk->length);

    memcpy(&chunk->type, chunk->data_ptr + 4 * sizeof(uint8_t),
           4 * sizeof(uint8_t));

    printf("Chunk type: %s\n", chunk->type);

    memcpy(&chunk->crc, chunk->data_ptr + 8 * sizeof(uint8_t) + chunk->length,
           4 * sizeof(uint8_t));

    printf("Chunk crc: %02X\n", chunk->crc);

    file = realloc(file, sizeof(PngFile) + 1 * sizeof(uint8_t **));
    file->chunks[chunk_idx] = chunk;

    chunk_idx++;

    chunk_data_ptr = chunk_data_ptr + chunk_size + 1;
    if (chunk_data_ptr >= file->ptr + file->filesize) {
      break;
    }
  }
  file->num_chunks = chunk_idx + 1;
}

bool png_verify(PngFile *file) {
  uint64_t checksum = 0;
  memcpy(&checksum, file->ptr, 8 * sizeof(uint8_t));
  if (checksum == PNG_HEADER_VALUE) {
    DEBUG("VERIFIED");
    file->header->value = PNG_HEADER_VALUE;
    file->header->verified = true;
    return true;
  }
  return false;
}

void png_free(PngFile *file) {
  file->chunk_ptr = NULL;
  for (int i = 0; i < file->num_chunks; i++) {
    free(file->chunks[i]);
  }
  free(file->header);
  free(file->ptr);
  free(file);
}
