cmake_minimum_required(VERSION 3.1)

project(client1)

set_source_files_properties(client1.cpp PROPERTIES LANGUAGE CXX )

add_executable(client1 client1.cpp)

target_link_libraries(client1 -lpthread)