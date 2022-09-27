#include <SDL.h>
#include <lz4.h>
#include <lz4hc.h>

int IMG_SaveLZ4_RW (SDL_Surface* surface, SDL_RWops* dst, int freedst, int hc)
{
  Uint16 width = (Uint16)(surface->w);
  Uint16 height = (Uint16)(surface->h);
  Uint32 surface_format = surface->format->format;

  SDL_RWwrite (dst, &width, sizeof(width), 1);
  SDL_RWwrite (dst, &height, sizeof(height), 1);
  SDL_RWwrite (dst, &surface_format, sizeof(surface_format), 1);
  Uint8 bpp = surface->format->BytesPerPixel;
  Uint32 uncompressed_size = width * height * (Uint32)bpp;

  const char* uncompressed_buffer = (const char*)(surface->pixels);
  int max_lz4_size = LZ4_compressBound (uncompressed_size);
  char* compressed_buffer = malloc (max_lz4_size);
  int true_size = -1;

  if (hc)
    true_size = LZ4_compress_HC(uncompressed_buffer, compressed_buffer,
                                uncompressed_size, max_lz4_size,
                                LZ4HC_CLEVEL_MAX);
  else
    true_size = LZ4_compress_default (uncompressed_buffer, compressed_buffer,
                                      uncompressed_size, max_lz4_size);

  SDL_RWwrite (dst, &true_size, sizeof(int), 1);
  SDL_RWwrite (dst, compressed_buffer, 1, true_size);

  free (compressed_buffer);

  if (freedst)
    SDL_RWclose (dst);

  return 0;
}

int IMG_SaveLZ4 (SDL_Surface* surface, const char* file, int hc)
{
  SDL_RWops* dst = SDL_RWFromFile (file, "wb");
  return (dst ? IMG_SaveLZ4_RW (surface, dst, 1, hc) : -1);
}

SDL_Surface* IMG_LoadLZ4_RW (SDL_RWops* src, int freesrc)
{
  Uint16 width;
  Uint16 height;
  Uint32 surface_format;
  int compressed_size;

  SDL_RWread (src, &width, sizeof(width), 1);
  SDL_RWread (src, &height, sizeof(height), 1);
  SDL_RWread (src, &surface_format, sizeof(surface_format), 1);
  SDL_RWread (src, &compressed_size, sizeof(compressed_size), 1);

  SDL_Surface* out = SDL_CreateRGBSurfaceWithFormat (0, width, height, 32, surface_format);
  Uint8 bpp = out->format->BytesPerPixel;
  Uint32 uncompressed_size = width * height * (Uint32)bpp;

  char* compressed_buffer = malloc (compressed_size);
  SDL_RWread (src, compressed_buffer, 1, compressed_size);
  char* uncompressed_buffer = (char*)(out->pixels);
  LZ4_decompress_safe (compressed_buffer, uncompressed_buffer, compressed_size, uncompressed_size);
  free (compressed_buffer);

  if (freesrc)
    SDL_RWclose (src);

  return out;
}

SDL_Surface* IMG_LoadLZ4 (const char* file)
{
  SDL_RWops* src = SDL_RWFromFile (file, "rb");
  return (src ? IMG_LoadLZ4_RW (src, 1) : NULL);
}
