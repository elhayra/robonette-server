
#include <robonette/manager.h>

namespace rbnt
{
    /* test msg */
    /*byte msg1[49] = {
              data type  1,
              dataTag  104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
              dataUnits  104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
              data  0,0,0,0,0,0,0,2
    };*/

    void Manager::loop()
    {
        //TODO: get bytes from client (commands)
    }

    bool Manager::sendBytes(const byte bytes[], size_t size) const
    {
        int bytes_sent = server_.writeBytes(bytes, size);
        if (bytes_sent == size)
            return true;
        return false;
    }

    bool Manager::writeImg(std::string tag,
                           const sensor_msgs::Image::ConstPtr &img_msg) const
    {
        ImgMsg msg;
        msg.setTag(tag);
        msg.setEncoding(img_msg->encoding);
        msg.setHeight(img_msg->height);
        msg.setWidth(img_msg->width);
        msg.setStep(img_msg->step);
        msg.isBigEndian(img_msg->is_bigendian);
        msg.setData(img_msg->data);

        byte msg_bytes[ImgMsg::SIZE];
        msg.toBytes(msg_bytes, ImgMsg::SIZE);
        return sendBytes(msg_bytes, ImgMsg::SIZE);
    }

    bool Manager::writeInfo(std::string tag,
                            int32_t data,
                            std::string units) const
    {
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