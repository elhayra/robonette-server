
#include <robonette/manager.h>

namespace rbnt
{

    void Manager::loop()
    {
        //TODO: get bytes from client (commands)
    }

    bool Manager::sendBytes(const byte bytes[], size_t size) const
    {
        int bytes_sent = 0;
        while (bytes_sent < size)
        {
            int n = server_.writeBytes(bytes + bytes_sent, size - bytes_sent);
            if (n == -1)
                break;  // ERROR client disconnected

            bytes_sent += n;
        }


        fprintf(stderr, "sent: %i\n", bytes_sent);
        if (bytes_sent == size)
            return true;
        return false;
    }

    bool Manager::writeImg(std::string tag,
                           const sensor_msgs::CompressedImage::ConstPtr &img_msg) const
    {
        const size_t msg_size = ImgMsg::FIELDS_SIZE +
                                (img_msg->data.size());

        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::IMAGE);
        header.setMsgSize(msg_size);

        byte header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        ImgMsg msg;
        msg.setTag(tag);
        msg.setEncoding(img_msg->format);
        msg.setData(img_msg->data);
        msg.setHeight(img_msg->data.size());

        byte msg_bytes[msg_size];
        msg.toBytes(msg_bytes, msg_size);
        return sendBytes(msg_bytes, msg_size);
    }

    bool Manager::writeImg(std::string tag,
                           const sensor_msgs::Image::ConstPtr &img_msg) const
    {
        const size_t msg_size = ImgMsg::FIELDS_SIZE +
                (img_msg->step * img_msg->height);

        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::IMAGE);
        header.setMsgSize(msg_size);

        byte header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        ImgMsg msg;
        msg.setTag(tag);
        msg.setEncoding(img_msg->encoding);
        msg.setHeight(img_msg->height);
        msg.setWidth(img_msg->width);
        msg.setStep(img_msg->step);
        msg.isBigEndian(img_msg->is_bigendian);
        msg.setData(img_msg->data);

 //       for (int i=0; i<img_msg->step * img_msg->height;i++)
  //          printf("%i:\n",img_msg->data[i]);

        byte msg_bytes[msg_size];
        msg.toBytes(msg_bytes, msg_size);
        return sendBytes(msg_bytes, msg_size);
    }

    bool Manager::writeInfo(std::string tag,
                            int32_t data,
                            std::string units) const
    {
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::INFO);
        header.setMsgSize(InfoMsg::SIZE);

        byte header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        InfoMsg msg;
        msg.setDataType(InfoMsg::DataType::INT32);
        msg.setDataTag(tag);
        msg.setDataUnits(units);
        msg.setDataInt32(data);

        byte msg_bytes[InfoMsg::SIZE];
        msg.toBytes(msg_bytes, InfoMsg::SIZE);
        return sendBytes(msg_bytes, InfoMsg::SIZE);
    }

    bool Manager::writeInfo(std::string tag,
                            float data,
                            std::string units) const
    {
        RbntHeader header;
        header.setHeaderStart(RbntHeader::VALID_HEADER_START);
        header.setMsgType(RbntHeader::MsgType::INFO);
        header.setMsgSize(InfoMsg::SIZE);

        byte header_bytes[RbntHeader::SIZE];
        header.toBytes(header_bytes, RbntHeader::SIZE);
        sendBytes(header_bytes, RbntHeader::SIZE);

        InfoMsg msg;
        msg.setDataType(InfoMsg::DataType::FLOAT32);
        msg.setDataTag(tag);
        msg.setDataUnits(units);
        msg.setDataFloat32(data);

        byte msg_bytes[InfoMsg::SIZE];
        msg.toBytes(msg_bytes, InfoMsg::SIZE);
        return sendBytes(msg_bytes, InfoMsg::SIZE);
    }

    bool Manager::startServer()
    {
        server_.bindTo(5005);
        server_.startListen();
        return true;
    }

    void Manager::waitForClient()
    {
        server_.acceptClient();
    }
}