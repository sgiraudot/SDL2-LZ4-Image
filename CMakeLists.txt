cmake_minimum_required (VERSION 3.2)
project (sosage)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SDL_LZ4_IMAGE_DEPENDENCIES_OKAY true)

find_package(SDL2 REQUIRED)
if (NOT SDL2_FOUND)
  message(STATUS "SDL2 is required and not found")
  set(SDL_LZ4_IMAGE_DEPENDENCIES_OKAY false)
endif()

find_package(SDL2_image REQUIRED)
if (NOT SDL2_IMAGE_FOUND)
  message(STATUS "SDL2 Image is required and not found")
  set(SDL_LZ4_IMAGE_DEPENDENCIES_OKAY false)
endif()

find_package(LZ4 REQUIRED)
if (NOT LZ4_FOUND)
  message(STATUS "LZ4 is required and not found")
  set(SDL_LZ4_IMAGE_DEPENDENCIES_OKAY false)
endif()

if (NOT SDL_LZ4_IMAGE_DEPENDENCIES_OKAY)
  message(STATUS "Some dependencies are missing (see below), project won't be compiled")
  return()
endif()

file(GLOB_RECURSE SDL_LZ4_IMAGE_SRC "src/*.c")
include_directories(include)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${LZ4_INCLUDE_DIR})

add_executable(SDL_lz4_image_converter "SDL_lz4_image_converter.c" ${SDL_LZ4_IMAGE_SRC})
target_link_libraries(SDL_lz4_image_converter "${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${LZ4_LIBRARY}")
