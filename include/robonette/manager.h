
#ifndef ROBONETTE_SERVER_COMM_MANAGER_H
#define ROBONETTE_SERVER_COMM_MANAGER_H

#include <robonette/tcp_server.h>
#include <robonette/protocol/InfoMsg.h>
#include <iostream>

namespace rbnt
{
    class Manager
    {
    private:
        TcpServer server_;
        bool sendInfoMsg(const InfoMsg& msg);

    public:
        bool startServer();
        void waitForClient();

        bool writeInfo(std::string tag,
                       int32_t data,
                       std::string units);
        bool writeInfo(std::string tag,
                       float data,
                       std::string units);
        //TODO: create writeInfo for all data types

        void closeServer();
        void loop();
    };
}



#endif //ROBONETTE_SERVER_COMM_MANAGER_H
