
#ifndef ROBONETTE_SERVER_COMM_MANAGER_H
#define ROBONETTE_SERVER_COMM_MANAGER_H

#include <robonette/tcp_server.h>
#include <robonette/protocol/messages/info_msg.h>
#include <robonette/protocol/messages/img_msg.h>
#include <sensor_msgs/Image.h>
#include <iostream>

namespace rbnt
{
    class Manager
    {
    private:
        TcpServer server_;
        bool sendBytes(const byte bytes[], size_t size) const;

    public:
        bool startServer();
        void waitForClient();

        bool writeInfo(std::string tag,
                       int32_t data,
                       std::string units) const;
        bool writeInfo(std::string tag,
                       float data,
                       std::string units) const;
        //TODO: create writeInfo for all data types

        bool writeImg(std::string tag,
                      const sensor_msgs::Image::ConstPtr &img_msg) const;

        void closeServer();
        void loop();
    };
}



#endif //ROBONETTE_SERVER_COMM_MANAGER_H
