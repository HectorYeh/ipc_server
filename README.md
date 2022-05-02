# ipc_server_client

This is an IPC server/client example.


## Environment
 - OS: Ubuntu 18.04
 - Cmake: 3.10.2


## Installation

### Compile
    mkdir build
    cd build
    cmake ..
    make

or
  
    sh autobuild.sh
    

### Run

1. ./server
2. ./client3 or ./client2
3. ./client3 or ./client2
4. ./client1
5. while all clients are ready, then server will show "Server is ready." msg
6. input integers and click [ENTER] 
7. clients will show the results (Mean/Median/Mode)
