

#ifndef ROBONETTE_SERVER_PACKET_CELL_H
#define ROBONETTE_SERVER_PACKET_CELL_H

#include <tcp_server.h>

class PacketCell
{
private:
    int index_;
public:
    PacketCell(int index) { index_ = index; }
    int getIndex() { return index_; }
    virtual bool fromBytes(byte bytes[], size_t size) = 0;

};

#endif //ROBONETTE_SERVER_PACKET_CELL_H