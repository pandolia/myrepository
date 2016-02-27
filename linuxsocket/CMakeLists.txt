project(linuxsocket)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_C_FLAGS "-Wall -O2")
add_executable(nslookup ./nslookup.c)
add_executable(echo-client ./echo-client.c)
add_executable(echo-server ./echo-server.c)

