
#ifndef ROBONETTE_SERVER_BOOL_CELL_H
#define ROBONETTE_SERVER_BOOL_CELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class BoolCell : public PacketCell
    {
    private:
        bool value_ = false;
    public:
        static const int SIZE = 1;
        BoolCell(int index, bool value) : PacketCell(index) { setValue(value); }
        BoolCell(int index) : PacketCell(index) {}
        bool fromBytes(const uint8_t bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            value_ = bytes[getIndex()];
            return true;
        }
        void toBytes(uint8_t bytes[]) const
        {
            bytes[getIndex()] = value_;
        };
        void setValue(const bool &value) { value_ = value; }

    };
}

#endif //ROBONETTE_SERVER_BOOL_CELL_H
