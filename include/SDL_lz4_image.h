#ifndef SDL_LZ4_IMAGE_H
#define SDL_LZ4_IMAGE_H

#include <SDL_lz4_image/utils.h>
#include <SDL.h>

int IMG_SaveLZ4_RW (SDL_Surface* surface, SDL_RWops* dst, int freedst, int hc);
int IMG_SaveLZ4 (SDL_Surface* surface, const char* file, int hc);
SDL_Surface* IMG_LoadLZ4_RW (SDL_RWops* src, int freesrc);
SDL_Surface* IMG_LoadLZ4 (const char* file);

#endif // SDL_LZ4_IMAGE_H
