//#include <fcntl.h>
//#include <unistd.h>
//#include <system_error>
#include <chrono>
#include <iostream>

#include <capnp/rpc-twoparty.h>
#include <capnp/capability.h>
#include <kj/async-io.h>
#include <kj/async.h>

#include "bench.capnproto.h"

#include <string>
//#include <vector>
#include <cstdint>


int main(int argc, char* argv[])
{
  std::string ipAddr = "localhost";
  int port = 8888;
  int64_t loopCount = 100;

  if (argc < 3) {
    std::cout << argv[0] << " <ipaddr> <loop_count> " << std::endl;
    exit(1);
  }
  else {
    ipAddr = argv[1];
    loopCount = atoll(argv[2]);
  }


  auto ioContext = kj::setupAsyncIo();

  auto address = ioContext.provider->getNetwork()
    .parseAddress(ipAddr.c_str(), port).wait(ioContext.waitScope);

  auto connection = address->connect().wait(ioContext.waitScope);

  capnp::TwoPartyClient client(*connection);

  auto cap = client.bootstrap().castAs<benchmark::Database>();

  auto array = kj::heapArrayBuilder<
    kj::Promise<
      capnp::Response<
        benchmark::Database::GetResults>>>(loopCount);

  char str[] = "abcdefgh";

  auto start = std::chrono::high_resolution_clock::now();
  for (int64_t i = 0; i < loopCount ; i++)
  {
    auto req = cap.getRequest();
    req.setKey(::capnp::Data::Reader(reinterpret_cast<const kj::byte*>(str), 8));
    auto p = req.send();
    array.add(kj::mv(p));
  }

  auto comboPromise = kj::joinPromises(array.finish());
  comboPromise.wait(ioContext.waitScope);

  auto finish = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

  std::cout
    << "loopcount=" << loopCount
    << ":time=" << duration
    << ":latency=" << duration/loopCount << " microsec"
    << std::endl;
}

