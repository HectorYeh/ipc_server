cmake_minimum_required(VERSION 3.1)

project(server)

set_source_files_properties(testApplication.cpp PROPERTIES LANGUAGE CXX )

add_compile_options(-fpermissive)

add_executable(server server.cpp)