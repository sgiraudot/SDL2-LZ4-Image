# - Try to find
# Once done this will define
#
#  LZ4_FOUND = LZ4_FOUND - TRUE
#  LZ4_INCLUDE_DIR - include directory for LZ4
#  LZ4_LIBRARY   - the library

# first look in user defined locations
find_path (LZ4_INCLUDE_DIR
  NAMES lz4.h
  PATHS /usr/local/include/ /usr/include
  ENV LZ4_INC_DIR
  )

find_library(LZ4_LIBRARY
  NAMES lz4
  PATHS ENV LD_LIBRARY_PATH
  ENV LIBRARY_PATH
  /usr/local/lib
  /usr/lib
  ${LZ4_INCLUDE_DIR}/../lib
  ENV LZ4_LIB_DIR
  )

if(LZ4_LIBRARY AND LZ4_INCLUDE_DIR)
  set(LZ4_FOUND TRUE)
endif()

