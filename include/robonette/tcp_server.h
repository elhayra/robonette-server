#ifndef ROBONETTE_TCP_SERVER_H
#define ROBONETTE_TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace rbnt
{
    using byte = unsigned char;

    class TcpServer
    {
    private:

        int sockfd_, newsockfd_;
        socklen_t clilen_;
        struct sockaddr_in serv_addr_, cli_addr_;

    public:
        bool bindTo(int port);
        void startListen();
        bool acceptClient();
        int writeBytes(byte bytes[], size_t size);
        int  readBytes(byte bytes[], size_t size);
        void closeServer();

    };
}


#endif




