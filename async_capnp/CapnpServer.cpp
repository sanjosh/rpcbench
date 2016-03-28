#include <fcntl.h>
#include <unistd.h>
#include <system_error>

#include <capnp/rpc-twoparty.h>
#include <kj/async-io.h>
#include <kj/async.h>

#include "bench.capnproto.h"

#include <glog/logging.h>

#include <string>
#include <vector>
#include <cstdint>

class SessionImpl : public benchmark::Database::Server
{
  public:
  SessionImpl()
  {
  }

  virtual ::kj::Promise<void> get(GetContext context) override
  {
    context.getResults().setValue(context.getParams().getKey());
    return kj::READY_NOW;
  }
  
};

int main(int argc, char* argv[])
{
  std::string addr_ = "*";
  int port_ = 8888;

  auto ioContext = kj::setupAsyncIo();

  capnp::TwoPartyServer server(kj::heap<SessionImpl>());

  auto address = ioContext.provider->getNetwork()
    .parseAddress(addr_, port_).wait(ioContext.waitScope);
  
  auto listener = address->listen();
  auto listenPromise = server.listen(*listener);

  listenPromise.wait(ioContext.waitScope);
}
