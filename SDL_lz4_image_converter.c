#include <stdio.h>
#include <stdlib.h>

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

  for (int i = 1; i < argc; ++ i)
  {
    const char* filename = argv[i];
    if (string_ends_with (filename, ".sdl_surface.lz4"))
    {
      printf ("Decompressing %s\n", filename);
      SDL_Surface* src = IMG_LoadLZ4 (filename);
      if (src == NULL)
      {
        printf ("Error while reading input image\n");
        return EXIT_FAILURE;
      }

      char* output_filename = string_replace_extension (filename, "png");
      IMG_SavePNG (src, output_filename);
      free (output_filename);
    }
    else
    {
      printf ("Compressing %s\n", filename);
      SDL_Surface* src;
      if (string_ends_with (filename, ".bmp"))
        src = SDL_LoadBMP (filename);
      else
        src = IMG_Load (filename);

      if (src == NULL)
      {
        printf ("Error while reading input image\n");
        printf ("%s", SDL_GetError());
        return EXIT_FAILURE;
      }

      char* output_filename = string_replace_extension (filename, "sdl_surface.lz4");
      IMG_SaveLZ4 (src, output_filename, 1);
      free (output_filename);
    }
  }

  IMG_Quit ();
  SDL_Quit ();

  return EXIT_SUCCESS;
}
