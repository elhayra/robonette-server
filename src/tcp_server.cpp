/* synchronized TCP server */

#include <robonette/tcp_server.h>

namespace rbnt
{
    bool TcpServer::bindTo(int port)
    {
        if (port < 0 || port > 65535)
            return false;
        sockfd_ =  socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd_ < 0)
            return false; //error opening socket

        bzero((char *) &serv_addr_, sizeof(serv_addr_));
        serv_addr_.sin_family = AF_INET;
        serv_addr_.sin_addr.s_addr = INADDR_ANY;
        serv_addr_.sin_port = htons(port);

        if (bind(sockfd_, (struct sockaddr *) &serv_addr_, sizeof(serv_addr_)) < 0)
            return false; //error binding
        return true;
    }

    void TcpServer::startListen()
    {
        listen(sockfd_, 5);
    }

    bool TcpServer::acceptClient()
    {
        clilen_ = sizeof(cli_addr_);
        newsockfd_ = accept(sockfd_, (struct sockaddr *) &cli_addr_, &clilen_);
        if (newsockfd_ < 0)
            return false; //error accepting client
        return true; //got connection
    }

    int TcpServer::readBytes(byte *bytes, size_t size)
    {
        return read(newsockfd_, bytes, size);
    }

    int TcpServer::writeBytes(byte bytes[], size_t size)
    {
        return send(newsockfd_, bytes, size, 0);
    }

    void TcpServer::closeServer()
    {
        close(newsockfd_);
        close(sockfd_);
    }
}
