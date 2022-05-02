cmake_minimum_required(VERSION 3.1)

project(client2)

set_source_files_properties(client2.cpp PROPERTIES LANGUAGE CXX )

add_executable(client2 client2.cpp)

# target_link_libraries(client -lpthread)