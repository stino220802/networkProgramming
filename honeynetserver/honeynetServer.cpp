

#include "honeynetServer.h"

std::map<std::string, int> map1 ;


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
    std::string requestRecentSubs = "requestRecentSubs";
    auto * msg = new zmq::message_t();
    int count1 = 0;
    bool echoStatus = false;
    int echoCount = 0;
    //amazingService!>reverseShell>
    while(true)
    {
        subscriber.recv( msg );

        std::string temp( (char*) msg->data(), msg->size());
        //std::cout << temp << std::endl;
        count1++;
        if((msg->to_string().compare(fuckArthurPhilipDent)) == 0){
            continue;
        }
        else if((msg->to_string().find("amazingService!>activateSpammer>")) != std::string::npos){
            printf("spammer werkt");
            std::string r = msg->to_string().substr(32, msg->to_string().length());
            std::cout << "string : " << r;
            if((r.find("amazingService!")) != std::string::npos || (r.find("activateSpammer")) != std::string::npos){
                continue;
            }
            spammerInstance(r);
        }
        else if((msg->to_string().find("amazingService!>reverseShell"))!= std::string::npos){
            printf("werkt");
            std::string a = msg->to_string().substr(28, msg->to_string().length());
            std::string temp2;
            temp2 = "amazingService!>theBigSecret>" + a;
            sendCommand(temp2);
        }
        else if((msg->to_string().find("amazingService!>activateLoadSpammer>")) != std::string::npos){
            std::string b = msg->to_string().substr( 36, msg->to_string().length());
            loadSpammer(b);
        }
        else if((msg->to_string().find("amazingService!>activateEchoSpammer>")) != std::string::npos){
            echoStatus = true;
            std::string z = msg->to_string().substr(36, msg->to_string().length());
            echoCount = stoi(z);

        }
        else if((msg->to_string().find("amazingService!>deactivateEchoSpammer>")) != std::string::npos){
            echoStatus = false;
        }
        else if((msg->to_string().find("amazingService!")) == std::string::npos && echoStatus){
            std::string x = msg->to_string();
            auto it = map1.find(x);
            if(it != map1.end()){
                it->second--;
                if(it->second == 0){
                    it = map1.erase(it);
                }
            }
            else{
                echoSpammer(x, echoCount);
                map1.insert(std::make_pair(x, echoCount));
            }
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
            //printf("count++\n");
        }
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

void honeynetServer::spammerInstance(const std::string& basicString) {
    try
    {
        zmq::context_t context(1);

        //Outgoing message go out through here
        zmq::socket_t ventilator( context, ZMQ_PUSH );
//        ventilator.connect( "tcp://localhost:24041" );
        ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
        time_t endwait;
        int seconds = 1;
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

void honeynetServer::sendCommand(const std::string& basicString) {
    zmq::context_t context(1);
    zmq::socket_t ventilator( context, ZMQ_PUSH );
    ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
    try {
        ventilator.send(basicString.c_str(), basicString.size());
        // std::cout << "Pushed : [exampe>quest>stijnVerhoeven]" << std::endl;
    }
    catch(zmq::error_t& e) {
        std::cout << e.what() << std::endl;
    }
}

void honeynetServer::loadSpammer(std::string b) {

    if((b.find("amazingService!")) != std::string::npos || (b.find("activateLoadSpammer")) != std::string::npos){
        return;
    }



    std::size_t pos = b.find(">");
    std::string str1 = b.substr(0, pos);
    std::string str2 = b.substr(pos+1);
    std::size_t pos1 = str2.find("%%EXPAND%%");
    std::string str3 = str2.substr(0, pos1);

    int num = stoi(str1);
    //create string with characters (they can be specified in the string pattern)
    std::string pattern("bart");
    auto pattern_it = pattern.begin();
    std::string str4(num, '\0');
    std::generate(str4.begin(), str4.end(), [&]() -> char{
        if(pattern_it == pattern.end())
            pattern_it = pattern.begin();
        return *pattern_it++;
    });
    str4 = str3 + str4 + ">";
    std::cout << str4 << std::endl;
    zmq::context_t context(1);

    //Outgoing message go out through here
    zmq::socket_t ventilator( context, ZMQ_PUSH );
//        ventilator.connect( "tcp://localhost:24041" );
    ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
    time_t endwait;
    int seconds = 1;
    endwait = time (NULL) + seconds;
    while(time(NULL) < endwait)
    {
        try {
            ventilator.send(str4.c_str(), str4.size());

        }
        catch(zmq::error_t& e) {
            std::cout << e.what() << std::endl;
        }
    }
}

void honeynetServer::echoSpammer(std::string x, int count) {
    zmq::context_t context(1);

    //Outgoing message go out through here
    zmq::socket_t ventilator( context, ZMQ_PUSH );
//        ventilator.connect( "tcp://localhost:24041" );
    ventilator.connect( "tcp://benternet.pxl-ea-ict.be:24041" );
    for(int i = 0; i < count; i++ ){
        try{
            ventilator.send(x.c_str(), x.size());
            printf("%d, %s", i, x.c_str());
        }
        catch(zmq::error_t& e){
            std::cout << e.what() << std::endl;
        }
    }
}
