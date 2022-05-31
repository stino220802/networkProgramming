

#include "honeynetServer.h"

[[noreturn]] void honeynetServer::sub() {

    std::map<std::string, int> zmqSubs;
    zmq::context_t context(1);
    int count = 0;
    zmq::socket_t subscriber( context, ZMQ_SUB );
    //subscriber.connect( "tcp://localhost:24042" );
    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0 );
    std::string fuckArthurPhilipDent = "example>quest!>Arthur Philip Dent>the ultimate answer to life the universe and everything?>";
    std::string spammer = "amazingService!>activateSpammer>";
    std::string requestRecentSubs = "amazingService!>requestRecentSubs";
    auto * msg = new zmq::message_t();
    int count1 = 0;
    while(true)
    {
        subscriber.recv( msg );

        std::string temp( (char*) msg->data(), msg->size());
        count1++;
        if((msg->to_string().compare(fuckArthurPhilipDent)) == 0){
            continue;
        }
        else if((msg->to_string().compare(requestRecentSubs)) == 0){
            sendRecentSubs();
        }
        else if((msg->to_string().find("activateSpammer")) != std::string::npos){
            printf("spammer werkt");
            std::string r = msg->to_string().substr(32, msg->to_string().length());
            std::cout << "string : " << r;
            spammerInstance(r);
        }

        auto it = zmqSubs.find(temp);
        if(it != zmqSubs.end()){
            it->second++;
        }
        else{
            zmqSubs.insert(std::make_pair(temp , 1));
        }
        if(count == 100){
            writeMapToFile(zmqSubs);
            zmqSubs.clear();
            count = 0;
        }
        else{
            count++;

        }
    }
}

void honeynetServer::sendRecentSubs() {
    printf("werkt");
    try {
        auto map1 = readFileToMap();
        int size = 0;
        size = map1.size();
        zmq::context_t context(1);
        zmq::socket_t socket(context, ZMQ_PUSH);
        socket.connect("tcp://benternet.pxl-ea-ict.be:24041");
        int i;
        int count = 0;
        int size2 = size;
        do{
            size /= 10;
            ++count;
        }while(size != 0);
        socket.send("amazingService?>size>%d", size, 16 + count);
        for (auto it = map1.begin(); it != map1.end(); ++it) {
            try {
                std::string sendtpc = ( "amazingService?>values>" + it->first + ">" + std::to_string(it->second));
                //socket.send(sendtpc.c_str(), sendtpc.size());
                printf("test");
            }
            catch (zmq::error_t &e) {
                std::cout << e.what() << std::endl;

            };
        };
    }
    catch(zmq::error_t & ex ){
        std::cerr << "Caught an exception : " << ex.what();
    }
}

std::map<std::string, int> honeynetServer::readFileToMap() {
    std::map<std::string, int> map1;
    std::ifstream paramFile;
    paramFile.open("honeylog.txt");
    std::string line;
    std::string key;
    double value;
    while(paramFile.good()) {
        std::getline(paramFile, line);
        std::istringstream ss(line);
        ss >> key >> value;
        map1[key] = value;
    }
    paramFile.close();
    return map1;
}

void honeynetServer::writeMapToFile(std::map<std::string, int> map1) {
    int count = 0;
    if (map1.empty()) {
        return;
    }
    FILE *fp = fopen("honeylog.txt", "w");

    if (!fp) {
        std::cout << "error with file: " << errno << std::endl;
        return;
    }

    for (auto &it: map1) {
        fprintf(fp, "%s %d\n", it.first.c_str(), it.second);
    }
    fclose(fp);

}

void honeynetServer::spammerInstance(std::string basicString) {
    try
    {
        zmq::context_t context(1);

        //Outgoing message go out through here
        zmq::socket_t ventilator( context, ZMQ_PUSH );
//        ventilator.connect( "tcp://localhost:24041" );
        ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        time_t endwait;
        int seconds = 4;
        endwait = time (NULL) + seconds;
        while(time(NULL) < endwait)
        {
            try {
                ventilator.send(basicString.c_str(), basicString.size());
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

}
