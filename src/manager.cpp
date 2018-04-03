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


#include <robonette/manager.h>

namespace rbnt
{

    void Manager::loop()
    {
        //TODO: get bytes from client (commands)
    }

    bool Manager::sendBytes(const uint8_t bytes[], size_t size)
    {
        int bytes_sent = 0;
        while (bytes_sent < size)
        {
            int n = server_.writeBytes(bytes + bytes_sent, size - bytes_sent);
            if (n == -1) // client disconnected
                return false;
            bytes_sent += n;
        }



        fprintf(stderr, "sent: %i\n", bytes_sent);
        if (bytes_sent == size)
            return true;
        return false;
    }

    bool Manager::writeImg(std::string tag,
                           const sensor_msgs::CompressedImage::ConstPtr &img_msg)
    {
        // build msg
        CompressedImgMsg msg;
        msg.setTag(tag);
        msg.setFormat(img_msg->format);
        msg.setImgSize(img_msg->data.size());
        msg.setData(img_msg->data);

        const size_t msg_size = msg.getSize();

        // build header
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::COMPRESSED_IMAGE);
        header.setMsgSize(msg_size);

        // send header
        uint8_t header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        // send msg
        uint8_t msg_bytes[msg_size];
        msg.toBytes(msg_bytes, msg_size);
        return sendBytes(msg_bytes, msg_size);
    }

    bool Manager::writeImg(std::string tag,
                           const sensor_msgs::Image::ConstPtr &img_msg)
    {
        // build msg
        ImgMsg msg;
        msg.setTag(tag);
        msg.setEncoding(img_msg->encoding);
        msg.setHeight(img_msg->height);
        msg.setWidth(img_msg->width);
        msg.setStep(img_msg->step);
        msg.isBigEndian(img_msg->is_bigendian);
        msg.setData(img_msg->data);

        const size_t msg_size = msg.getSize();

        // build header
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::IMAGE);
        header.setMsgSize(msg_size);

        // send header
        uint8_t header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        // send msg
        uint8_t msg_bytes[msg_size];
        msg.toBytes(msg_bytes, msg_size);
        return sendBytes(msg_bytes, msg_size);
    }

    bool Manager::writeInfo(std::string tag,
                            int32_t data,
                            std::string units)
    {
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::INFO);
        header.setMsgSize(InfoMsg::SIZE);

        uint8_t header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        InfoMsg msg;
        msg.setDataType(InfoMsg::DataType::INT32);
        msg.setDataTag(tag);
        msg.setDataUnits(units);
        msg.setDataInt32(data);

        uint8_t msg_bytes[InfoMsg::SIZE];
        msg.toBytes(msg_bytes, InfoMsg::SIZE);
        return sendBytes(msg_bytes, InfoMsg::SIZE);
    }

    bool Manager::writeInfo(std::string tag,
                            float data,
                            std::string units)
    {
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::INFO);
        header.setMsgSize(InfoMsg::SIZE);

        uint8_t header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        InfoMsg msg;
        msg.setDataType(InfoMsg::DataType::FLOAT32);
        msg.setDataTag(tag);
        msg.setDataUnits(units);
        msg.setDataFloat32(data);

        uint8_t msg_bytes[InfoMsg::SIZE];
        msg.toBytes(msg_bytes, InfoMsg::SIZE);
        return sendBytes(msg_bytes, InfoMsg::SIZE);
    }

    bool Manager::writeMap(const nav_msgs::OccupancyGrid::ConstPtr &map_msg)
    {
        size_t msg_size = MapMsg::FIELDS_SIZE + map_msg->data.size();
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::MAP);
        header.setMsgSize(msg_size);

        uint8_t header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        MapMsg msg;
        msg.setResolution(map_msg->info.resolution);
        msg.setWidth(map_msg->info.width);
        msg.setHeight(map_msg->info.height);
        msg.setData(map_msg->data);

        uint8_t msg_bytes[msg_size];
        msg.toBytes(msg_bytes, msg_size);
        return sendBytes(msg_bytes, msg_size);
    }

    bool Manager::startServer()
    {
        server_.bindTo(5005);
        server_.startListen();
        return true;
    }


}