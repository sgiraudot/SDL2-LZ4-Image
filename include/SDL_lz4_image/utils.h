/*
  SDL2 LZ4 Image
  Copyright (C) 2022 Simon Giraudot <sosage@ptilouk.net>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

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
