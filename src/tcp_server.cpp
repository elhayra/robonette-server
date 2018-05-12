/*******************************************************************************
* Copyright (c) 2018 Elhay Rauper
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*     * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
*     * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

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

    bool TcpServer::startListen()
    {
        int state = listen(sockfd_, 5);
        if (state == 0)
        {
            is_server_open_ = true;
            return true;
        }
        return false;
    }

    bool TcpServer::acceptClient()
    {
        clilen_ = sizeof(cli_addr_);
        newsockfd_ = accept(sockfd_, (struct sockaddr *) &cli_addr_, &clilen_);
        if (newsockfd_ < 0)
            return false; //error accepting client
        is_client_connected_ = true;
        return true; //got connection
    }

    bool TcpServer::readBytes(uint8_t *bytes, size_t size)
    {
        int bytes_read = 0;
        while (bytes_read < size)
        {
            int n = read(newsockfd_, bytes + bytes_read, size - bytes_read);
            if (n == 0 || n == -1) // client disconnected
            {
                closeClient();
                return false;
            }

            bytes_read += n;
        }
        //fprintf(stderr, "read: %i\n", bytes_read);
        return bytes_read == size;
    }

    bool TcpServer::writeBytes(const uint8_t bytes[], size_t size)
    {
        int bytes_sent = 0;
        while (bytes_sent < size)
        {
            int n = send(newsockfd_, bytes + bytes_sent, size - bytes_sent, 0);
            if (n == -1) // client disconnected
            {
                closeClient();
                return false;
            }
            bytes_sent += n;
        }
        //fprintf(stderr, "sent: %i\n", bytes_sent);
        return bytes_sent == size;
    }

    void TcpServer::closeServer()
    {
        is_client_connected_ = false;
        is_server_open_ = false;
        close(newsockfd_);
        close(sockfd_);
    }

    void TcpServer::closeClient()
    {
        is_client_connected_ = false;
        close(newsockfd_);
    }
}
