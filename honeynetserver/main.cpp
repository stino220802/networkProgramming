#include <iostream>
#include <thread>
#include <zmq.hpp>
#include <map>
#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#define sleep(n)    Sleep(n)

class context_t;

#endif
#include <string>
#include <vector>
#include <regex>
#include <sstream>


void pub();

[[noreturn]] void sub();


void writeMapToFile(std::map<std::string, int> map1);

void readFileToMap(std::map<std::string, int> map1);

int main()
{
    std::thread t2(sub);
    //std::thread t1(pub);
    //t1.join();
    t2.join();
    return 0;
}

void pub(){
    try
    {
        zmq::context_t context(1);

        //Outgoing message go out through here
        zmq::socket_t ventilator( context, ZMQ_PUSH );
//        ventilator.connect( "tcp://localhost:24041" );
        ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

        while(true)
        {
            try {
                ventilator.send("4 op een rij!>1>column full>", 27);
               // std::cout << "Pushed : [exampe>quest>stijnVerhoeven]" << std::endl;
            }
            catch(zmq::error_t& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught an exception : " << ex.what();
    }
    std::map<std::string, int> zmqSubs2;
    readFileToMap(zmqSubs2);
}

void readFileToMap(std::map<std::string, int> map1) {
    int count = 0;
    if( access("honeylog.txt", R_OK) < 0){
        std::cout << "error with file" << errno << std::endl;
        return;
    }
    FILE * fp = fopen("honeylog.txt", "r");
    if(!fp){
        std::cout << "error with file:" << errno << std::endl;
        return;
    }
    map1.clear();
    char * buf = 0;
    size_t buflen = 0;

    while(getline(&buf, &buflen, fp)){

    }
}

[[noreturn]] void sub(){
    std::map<std::string, int> zmqSubs;
    zmq::context_t context(1);
    int count = 0;
    //Incoming messages come in here
    zmq::socket_t subscriber( context, ZMQ_SUB );
    //subscriber.connect( "tcp://localhost:24042" );
    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0 );
    std::string fuckArthurPhilipDent = "example>quest!>Arthur Philip Dent>the ultimate answer to life the universe and everything?>";
    auto * msg = new zmq::message_t();
    while(true)
    {
        subscriber.recv( msg );

       std::string temp( (char*) msg->data(), msg->size());
        if((msg->to_string().compare(fuckArthurPhilipDent)) == 0){
            continue;
        }
       std::cout << "Subscribed : [" << temp << "]" << std::endl;

       auto it = zmqSubs.find(temp);
       if(it != zmqSubs.end()){
           it->second++;
       }
       else{
           zmqSubs.insert(std::make_pair(temp , 1));
       }
       if(count == 100){
           writeMapToFile(zmqSubs);
           count = 0;
       }
       else{
           count++;

       }
    }
}

void writeMapToFile(std::map<std::string, int> map1) {
    int count = 0;
    if(map1.empty()) {
        return;
    }
    FILE * fp = fopen("honeylog.txt", "w");

    if(!fp){
        std::cout << "error with file: " << errno << std::endl;
        return;
    }

    for(auto it = map1.begin(); it != map1.end(); ++it){
        fprintf(fp, "%s %d\n", it->first.c_str(), it->second);
    }
    fclose(fp);
    return;
    std::cout << "works" << std::endl;

}



