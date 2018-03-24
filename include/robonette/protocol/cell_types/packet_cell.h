

#ifndef ROBONETTE_SERVER_PACKET_CELL_H
#define ROBONETTE_SERVER_PACKET_CELL_H

#include <robonette/tcp_server.h>

namespace rbnt
{
    class PacketCell
    {
    private:
        int index_;
    public:
        PacketCell(int index) { index_ = index; }
        int getIndex() const { return index_; }
        virtual bool fromBytes(const uint8_t bytes[], size_t size) = 0;

    };
}

#endif //ROBONETTE_SERVER_PACKET_CELL_H
