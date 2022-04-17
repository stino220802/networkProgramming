#include <iostream>
#include <thread>
#include <zmq.hpp>
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
int main()
{
    std::thread t2(sub); 
    std::thread t1(pub);
    t1.join();
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
                ventilator.send("example>secretMessageService?>stijnverhoeven>Putin>f35de8fe1b9a8ea5bdd0d070508a46988849d201>#NoNukesPlease>", 107);
               // std::cout << "Pushed : [exampe>quest>stijnVerhoeven]" << std::endl;
            }
            catch(zmq::error_t& e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    catch( zmq::error_t & ex )
    {
        std::cerr << "Caught a exception : " << ex.what();
    }

}

[[noreturn]] void sub(){
    zmq::context_t context(1);

    //Incoming messages come in here
    zmq::socket_t subscriber( context, ZMQ_SUB );
    //subscriber.connect( "tcp://localhost:24042" );
    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0 );

    auto * msg = new zmq::message_t();
    long long count;
    while(true)
    {
        subscriber.recv( msg );
        count++;
        std::cout << count << std::endl;
       // std::cout << "Subscribed : [" << std::string( (char*) msg->data(), msg->size() ) << "]" << std::endl;
    }
}
