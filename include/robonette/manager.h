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

#ifndef ROBONETTE_SERVER_COMM_MANAGER_H
#define ROBONETTE_SERVER_COMM_MANAGER_H

#include <robonette/tcp_server.h>
#include <robonette/protocol/messages/info_msg.h>
#include <robonette/protocol/messages/map_msg.h>
#include <robonette/protocol/messages/img_msg.h>
#include <robonette/protocol/messages/compressed_img_msg.h>
#include <robonette/protocol/messages/cmd_msg.h>
#include <robonette/protocol/messages/rbnt_header.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <nav_msgs/OccupancyGrid.h>
#include <boost/thread.hpp>
#include <iostream>

namespace rbnt
{
    typedef void (*callback_function)(float, int);

    class Manager
    {
    private:
        TcpServer server_;
        // prevent parallel access to tcp socket
        boost::mutex comm_mutex_;
        boost::thread *read_thread_;
        std::vector<callback_function> cmd_cb_funcs_;

        void readLoop();

    public:
        Manager();
        ~Manager();
        bool writeInfo(std::string tag,
                       int32_t data,
                       std::string units);
        bool writeInfo(std::string tag,
                       float data,
                       std::string units);
        //TODO: create writeInfo for all data types

        bool writeImg(std::string tag,
                      const sensor_msgs::Image::ConstPtr &img_msg);
        bool writeImg(std::string tag,
                      const sensor_msgs::CompressedImage::ConstPtr &img_msg);

        bool writeMap(const nav_msgs::OccupancyGrid::ConstPtr &map_msg);

        bool startServer();
        void closeServer() { server_.closeServer(); }
        void closeClient() { server_.closeClient(); }
        bool isServerOpen() { return server_.isServerOpen(); }
        bool isClientConnected() { return server_.isClientConnected(); }
        void waitForClient();
        void subscribe(callback_function func) { cmd_cb_funcs_.push_back(func); }
    };
}



#endif //ROBONETTE_SERVER_COMM_MANAGER_H
