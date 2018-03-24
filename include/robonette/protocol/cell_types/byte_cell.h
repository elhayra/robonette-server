
#ifndef ROBONETTE_SERVER_BYTECELL_H
#define ROBONETTE_SERVER_BYTECELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class ByteCell : public PacketCell
    {
    private:
        uint8_t value_ = 0;
    public:
        static const int SIZE = 1;
        ByteCell(int index, uint8_t value) : PacketCell(index) { setValue(value); }
        ByteCell(int index) : PacketCell(index) {}
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

        void setValue(const uint8_t& value) { value_ = value; }
        uint8_t getValue() const { return value_; }

    };
}

#endif //ROBONETTE_SERVER_BYTECELL_H
