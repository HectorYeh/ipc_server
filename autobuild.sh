#!/bin/bash

echo "build server"
cd ./server
mkdir build
cd build
cmake ..
make


echo "build client1 (socket)"
cd ../../client1
mkdir build
cd build
cmake ..
make


echo "build client2 (pipe)"
cd ../../client2
mkdir build
cd build
cmake ..
make


echo "build client3 (shared memory)"
cd ../../client3
mkdir build
cd build
cmake ..
make


# echo "execute server & client"
# cd ../../
# server/build/server
# client/build/client