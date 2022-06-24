

#ifndef HONEYNETSERVER_HONEYNETSERVER_H
#define HONEYNETSERVER_HONEYNETSERVER_H
#include <zmq.hpp>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <thread>
#include <algorithm>
class honeynetServer {

public:
    [[noreturn]] void sub();



    static std::map<std::string, int> readFileToMap();

    static void writeMapToFile(std::map<std::string, int> map1);

    void spammerInstance(const std::string& basicString);

    static void sendCommand(const std::string& basicString);

    void loadSpammer(std::string basicString);

    void echoSpammer(std::string basicString, int count);
};


#endif //HONEYNETSERVER_HONEYNETSERVER_H
