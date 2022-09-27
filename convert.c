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
