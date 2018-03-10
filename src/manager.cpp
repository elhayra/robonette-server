
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

    bool Manager::sendInfoMsg(const InfoMsg& msg) const
    {
        byte msg_bytes[InfoMsg::SIZE];
        msg.toBytes(msg_bytes, InfoMsg::SIZE);

        /* send msg */
        int bytes_sent = server_.writeBytes(msg_bytes, InfoMsg::SIZE);
        if (bytes_sent == InfoMsg::SIZE)
            return true;
        return false;
    }

    bool Manager::sendImgMsg(const ImgMsg &msg) const
    {

    }

    bool Manager::writeImg(std::string tag,
                           const sensor_msgs::Image::ConstPtr &msg) const
    {

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
        sendInfoMsg(msg);
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
        sendInfoMsg(msg);
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