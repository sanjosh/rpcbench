
FIND_PROGRAM(THRIFT thrift HINTS /usr/local/bin)

ADD_CUSTOM_COMMAND(
  OUTPUT gen-cpp/Database.cpp gen-cpp/bench_constants.cpp gen-cpp/bench_types.cpp
  DEPENDS bench.thrift
  COMMAND ${THRIFT} --gen cpp -r bench.thrift
  COMMENT "generating thrift code"
  VERBATIM
  )


SET(SOURCES ThriftServer.cpp ThriftClient.cpp gen-cpp/bench_constants.cpp gen-cpp/bench_types.cpp gen-cpp/Database.cpp)

ADD_EXECUTABLE(ThriftServer ThriftServer.cpp gen-cpp/bench_constants.cpp gen-cpp/bench_types.cpp gen-cpp/Database.cpp)
ADD_EXECUTABLE(ThriftClient ThriftClient.cpp gen-cpp/bench_constants.cpp gen-cpp/bench_types.cpp gen-cpp/Database.cpp)

TARGET_LINK_LIBRARIES(ThriftServer thrift tcmalloc)
TARGET_LINK_LIBRARIES(ThriftClient thrift tcmalloc)
