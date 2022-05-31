

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
class honeynetServer {

public:
    [[noreturn]] void sub();

    void sendRecentSubs();

    std::map<std::string, int> readFileToMap();

    void writeMapToFile(std::map<std::string, int> map1);

    void spammerInstance(std::string basicString);
};


#endif //HONEYNETSERVER_HONEYNETSERVER_H
