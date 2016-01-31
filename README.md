# rpcbench
compare capnp vs thrift

How to run
$ cmake .
$ make

For thrift
$ cd thrift
$ ./ThriftServer&
$ ./ThriftClient localhost 100000
loopcount=100000:time=4098389:latency=40 microsec


For capnp
$ cd capnp
$ ./CapnpServer&
$ ./CapnpClient localhost 100000
loopcount=100000:time=11922413:latency=119 microsec

