
#include <manager.h>

void Manager::loop()
{
   byte msg1[49] = {
            /* data type */ 1,
            /* dataTag */ 104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
            /* dataUnits */ 104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
            /* data */ 0,0,0,0,0,0,0,2
   };

    InfoMsg msg;
    msg.setDataType(InfoMsg::DataType::INT32);
    msg.setDataTag("Battery");
    msg.setDataUnits("%");
    msg.setDataInt32(-60);
    byte msg_bytes[InfoMsg::SIZE];
    msg.toBytes(msg_bytes, InfoMsg::SIZE);

    int n = server_.writeBytes(msg_bytes, InfoMsg::SIZE);

}

bool Manager::startServer()
{
    /*InfoMsg msg;
    msg.setDataType(InfoMsg::DataType::INT32);
    msg.setDataTag("Battery");
    msg.setDataUnits("%");
    msg.setDataInt32(-60);
    byte msg_bytes[InfoMsg::SIZE];
    msg.toBytes(msg_bytes, InfoMsg::SIZE);

    server_.writeBytes(msg_bytes, InfoMsg::SIZE);*/

    server_.bindTo(5005);
    server_.startListen();
    return true;
}

void Manager::waitForClient()
{
    server_.acceptClient();
}