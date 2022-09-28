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

#include <SDL_lz4_image.h>

#include <SDL_image.h>

int main (int argc, char** argv)
{
  if (argc < 3)
  {
    printf ("Usage: %s [input] [output]\n", argv[0]);
    printf ("Usage (HC): %s [input] [output] -hc\n", argv[0]);
    return EXIT_SUCCESS;
  }

  int hc = 0;
  if (argc > 3)
    hc = 1;

  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  const char* input_filename = argv[1];
  SDL_Surface* input;
  if (string_ends_with (input_filename, ".bmp"))
    input = SDL_LoadBMP(input_filename);
  else
    input = IMG_Load (input_filename);

  SDL_PixelFormat* format = SDL_AllocFormat (SDL_PIXELFORMAT_ARGB8888);
  SDL_Surface *output = SDL_ConvertSurface(input, format, 0);

  const char* output_filename = argv[2];
  if (string_ends_with (output_filename, ".bmp"))
    SDL_SaveBMP (output, output_filename);
  else if (string_ends_with (output_filename, ".png"))
    IMG_SavePNG (output, output_filename);
  else if (string_ends_with (output_filename, ".lz4"))
    IMG_SaveLZ4 (output, output_filename, hc);
  else
  {
    printf("Error: unknown format %s\n", output_filename);
    return EXIT_FAILURE;
  }

  SDL_FreeSurface (output);
  SDL_FreeFormat (format);
  SDL_FreeSurface (input);
  IMG_Quit ();
  SDL_Quit ();

  return EXIT_SUCCESS;
}
