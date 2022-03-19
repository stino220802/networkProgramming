cmake_minimum_required(VERSION 3.21)
project(zermomqTest)

add_compile_definitions(ZMQ_STATIC)

#set(CMAKE_CXX_STANDARD 11)

include_directories(C:/zeromq/libzmq-4.3.4/include Sources/)
link_directories(C:/zeromq/libzmq-4.3.4/build/lib)

add_executable(zermomqTest main.cpp)

target_link_libraries(zermomqTest libzmq.a ws2_32 iphlpapi)
