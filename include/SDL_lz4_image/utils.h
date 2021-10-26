#ifndef SDL_LZ4_IMAGE_UTILS_H
#define SDL_LZ4_IMAGE_UTILS_H

#include <stdbool.h>
#include <string.h>

bool string_ends_with (const char* str, const char* end)
{
  const char* sub = strstr (str, end);
  return (sub != NULL && strlen(sub) == strlen(end));
}

char* string_replace_extension (const char* filename, const char* ext)
{
  int size = strlen(filename) - 3 + strlen(ext);
  char* out = malloc (size + 1);
  strcpy (out, filename);
  strcpy (out + strlen(filename) - 3, ext);
  return out;
}

#endif // SDL_LZ4_IMAGE_UTILS_H
