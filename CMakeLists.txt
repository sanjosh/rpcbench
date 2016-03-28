CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

SET (CMAKE_CXX_COMPILER "/usr/bin/g++")
SET (CMAKE_C_COMPILER "/usr/bin/gcc")

SET (CXX_STANDARD "c++11")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD}")

ADD_COMPILE_OPTIONS(
  -Wall
  -Wextra
  -Wstrict-aliasing
  -Wno-unused-parameter
  -Wno-missing-field-initializers
  -Wnon-virtual-dtor
  -Wchar-subscripts
  -Wpointer-arith
  -Woverloaded-virtual
  -Wformat
  -Wformat-security
  -Werror=format-security
  -fstack-protector-all
  -fPIE
  -fpie
  -fPIC
  -fpic
  -pipe
  -fdata-sections
  -ffunction-sections
)

ADD_SUBDIRECTORY(capnp)
ADD_SUBDIRECTORY(thrift)
ADD_SUBDIRECTORY(async_capnp)
