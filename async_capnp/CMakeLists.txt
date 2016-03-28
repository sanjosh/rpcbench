
FIND_PROGRAM(CAPNP capnp HINTS /usr/local/bin)

ADD_CUSTOM_COMMAND(
  OUTPUT bench.capnproto.c++
  DEPENDS bench.capnproto
  COMMAND ${CAPNP} compile -oc++ bench.capnproto
  COMMAND ${CMAKE_COMMAND} -E copy bench.capnproto.c++ bench.capnproto.cpp
  COMMENT "generating capnp code"
  VERBATIM
  )

SET(SOURCES CapnpServer.cpp CapnpClient.cpp bench.capnproto.cpp)

ADD_EXECUTABLE(AsyncCapnpServer CapnpServer.cpp bench.capnproto.c++)
ADD_EXECUTABLE(AsyncCapnpClient CapnpClient.cpp bench.capnproto.c++)

TARGET_LINK_LIBRARIES(AsyncCapnpServer capnp-rpc capnp kj-async kj tcmalloc)
TARGET_LINK_LIBRARIES(AsyncCapnpClient capnp-rpc capnp kj-async kj tcmalloc)
  
