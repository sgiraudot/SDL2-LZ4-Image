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

#ifndef SDL_LZ4_IMAGE_H
#define SDL_LZ4_IMAGE_H

#include <SDL_lz4_image/utils.h>
#include <SDL.h>

int IMG_SaveLZ4_RW (SDL_Surface* surface, SDL_RWops* dst, int freedst, int hc);
int IMG_SaveLZ4 (SDL_Surface* surface, const char* file, int hc);
SDL_Surface* IMG_LoadLZ4_RW (SDL_RWops* src, int freesrc);
SDL_Surface* IMG_LoadLZ4 (const char* file);

#endif // SDL_LZ4_IMAGE_H
