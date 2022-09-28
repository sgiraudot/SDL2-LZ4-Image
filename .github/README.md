# SDL2 LZ4 Image

***Note:** this repository is just a mirror of [the official
repository on Framagit](https://framagit.org/Gee/sdl2-lz4-image),
which should be considered as the most up-to-date and reliable source
for SDL2 LZ4 Image.*

This repository provides a way to convert images to a compressed
`SDL_Surface` format using the [LZ4](https://github.com/lz4/lz4)
compression library.

It also provides a way to create your own benchmark.

**This format was created for the game [Superfluous
Returnz](https://studios.ptilouk.net/superfluous-returnz/). The logic
behind it is explained in [this blog
post](https://studios.ptilouk.net/superfluous-returnz/blog/2022-09-28_compression.html)
along with results of a benchmark and additional explanations.**

## Compiling and running

This program has only been tested on GNU/Linux but should be
compatible on every platform compatible with SDL2 and LZ4.

Configuration is handled by CMake:

``` bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

## Compressing/decompressing

To convert an image into the SDL2 LZ4 format, run:

``` bash
$ ./convert [input.png/bmp/whatever] [output.lz4]
```

Add `-hc` at the end of the command to activate the LZ4 HC algorithm
(more efficient but longer to compress).

To convert images in batch, use:

``` bash
$ ./SDL_lz4_image_converter  file1.bmp file2.png file3.sdl_surface.lz4 [...]
```

BMP/PNG images will be compressed and saved using the same name with
the `.sdl_surface.lz4` extensions, LZ4 images will be decompressed and
saved with the same name with the `.png` extension.

## Profiling/benchmark

To profile on a set of images, run:

``` bash
$ ./profile file1.bmp file2.png file3.sdl_surface.lz4 [...]
```

This program outputs three values separated by a white space:
- the total time taken to read this files from disk to memory
- the total time taken to create the `SDL_Surface` structures
- the total time taken to create the `SDL_Texture` structures

In order to run a full benchmark on BMP/PNG/PNG(quant)/LZ4/LZ4(HC)
formats, run (from the root directory of the repository):

``` bash
$ python3 benchmark.py file1.bmp file2.png [...]
```

All provided images will be first converted to _all_ tested formats,
and then the profiling program will be used to compare them.

**Note:** this script may only work on GNU/Linux, and requires the
following dependencies:

- the [PNGQuant](https://pngquant.org/) software
- the [prettytable](https://pypi.org/project/prettytable/) Python3 package
