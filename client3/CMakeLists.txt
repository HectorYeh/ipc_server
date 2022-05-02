cmake_minimum_required(VERSION 3.1)

project(client3)

set_source_files_properties(client3.cpp PROPERTIES LANGUAGE CXX )

add_executable(client3 client3.cpp)

# target_link_libraries(client -lpthread)