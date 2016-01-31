/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <iostream>
#include <chrono>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/Database.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace bench;


int main(int argc, char* argv[]) {

  std::string ipAddr = "localhost";
  int64_t loopCount = 100;

  if (argc < 3) {
    std::cout << argv[0] << " <ipaddr> <loop_count> " << std::endl;
    exit(1);
  }
  else {
    ipAddr = argv[1];
    loopCount = atoll(argv[2]);
  }
  boost::shared_ptr<TTransport> socket(new TSocket(ipAddr, 9000));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  DatabaseClient client(protocol);

  try {
    transport->open();

    const std::string data = "abcdefgh";
    std::string ret;
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int64_t i = 0; i < loopCount; i++) {
      client.get(ret, data);
    }

    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

    std::cout 
      << "loopcount=" << loopCount 
      << ":time=" << duration 
      << ":latency=" << duration/loopCount << " microsec"
      << std::endl;

    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}
