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

  for (int i = 1; i < argc; ++ i)
  {
    const char* filename = argv[i];
    if (string_ends_with (filename, ".sdl_surface.lz4"))
    {
      printf ("Decompressing %s\n", filename);
      SDL_Surface* src = IMG_LoadLZ4 (filename);
      if (src == NULL)
      {
        printf ("Error while reading input image");
        return EXIT_FAILURE;
      }

      char* output_filename = string_replace_extension (filename, "png");
      IMG_SavePNG (src, output_filename);
      free (output_filename);
    }
    else
    {
      printf ("Compressing %s\n", filename);
      SDL_Surface* src = IMG_Load (filename);
      if (src == NULL)
      {
        printf ("Error while reading input image");
        return EXIT_FAILURE;
      }

      char* output_filename = string_replace_extension (filename, "sdl_surface.lz4");
      IMG_SaveLZ4 (src, output_filename);
      free (output_filename);
    }
  }

  return EXIT_SUCCESS;
}
