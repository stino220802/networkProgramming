cmake_minimum_required(VERSION 3.21)
project(reverseShell)

add_compile_definitions(ZMQ_STATIC)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/zeromq/libzmq-4.3.4/include Sources/)
link_directories(C:/zeromq/libzmq-4.3.4/build/lib)

add_executable(reverseShell
        reverseShell.cpp)

target_link_libraries(reverseShell libzmq.a ws2_32 iphlpapi)