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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL_lz4_image.h>

#include <SDL_image.h>

int main (int argc, char** argv)
{
  if (argc == 1)
  {
    printf ("Usage: %s [file1.bmp file2.png file3.sdl_surface.lz4 [...]\n", argv[0]);
    return EXIT_SUCCESS;
  }

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);
  SDL_Window* window = SDL_CreateWindow
                       ("",
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        10, 10, 0);

  SDL_Renderer* renderer = SDL_CreateRenderer (window, -1, 0);

  int nb_repeat = 100;
  double tread = 0., tsurface = 0., ttexture = 0.;
  for (int nb = 0; nb < nb_repeat; ++ nb)
    for (int i = 1; i < argc; ++ i)
    {
      const char* filename = argv[i];

      // Read file to memory
      clock_t begin = clock();
      SDL_RWops* file = SDL_RWFromFile(filename, "rb");
      Sint64 size = SDL_RWsize (file);
      char* buffer = malloc(size);
      SDL_RWread (file, buffer, 1, size);
      SDL_RWclose(file);
      clock_t end = clock();
      tread += (double)(end - begin) / CLOCKS_PER_SEC;

      // Create SDL Surface
      begin = clock();
      SDL_Surface* surface;
      SDL_RWops* src = SDL_RWFromMem (buffer, size);
      if (string_ends_with (filename, ".sdl_surface.lz4"))
        surface = IMG_LoadLZ4_RW(src, 0);
      else if (string_ends_with (filename, ".bmp"))
        surface = SDL_LoadBMP_RW (src, 0);
      else
        surface = IMG_Load_RW (src, 0);
      end = clock();
      tsurface += (double)(end - begin) / CLOCKS_PER_SEC;

      //    if (surface->format->format != SDL_PIXELFORMAT_ABGR8888)
      //      fprintf(stderr, "Warning, format of %s is %s\n", filename, SDL_GetPixelFormatName(surface->format->format));
      // Create SDL Texture
      begin = clock();
      SDL_Texture* texture = SDL_CreateTextureFromSurface (renderer, surface);
      end = clock();
      ttexture += (double)(end - begin) / CLOCKS_PER_SEC;

      // Cleaning (not profiled)
      SDL_DestroyTexture (texture);
      SDL_FreeSurface (surface);
      SDL_RWclose (src);
      free (buffer);
    }

  printf("%f %f %f\n", tread / nb_repeat, tsurface / nb_repeat, ttexture / nb_repeat);

  IMG_Quit ();
  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
  SDL_Quit ();

  return EXIT_SUCCESS;
}
