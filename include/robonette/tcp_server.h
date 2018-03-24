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
        int writeBytes(const uint8_t bytes[], size_t size) const;
        int  readBytes(uint8_t bytes[], size_t size) const;
        void closeServer();

    };
}


#endif




