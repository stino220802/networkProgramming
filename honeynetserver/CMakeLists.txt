cmake_minimum_required(VERSION 3.21)
project(honeynetserver)



add_compile_definitions(ZMQ_STATIC)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/zeromq/libzmq-4.3.4/include Sources/)
link_directories(C:/zeromq/libzmq-4.3.4/build/lib)

add_executable(honeynetserver main.cpp honeynetServer.cpp honeynetServer.h)

target_link_libraries(honeynetserver libzmq.a ws2_32 iphlpapi)
