
#ifndef ROBONETTE_SERVER_BYTECELL_H
#define ROBONETTE_SERVER_BYTECELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class ByteCell : public PacketCell
    {
    private:
        byte value_ = 0;
    public:
        static const int SIZE = 1;
        ByteCell(int index, byte value) : PacketCell(index) { setValue(value); }
        ByteCell(int index) : PacketCell(index) {}
        bool fromBytes(const byte bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            value_ = bytes[getIndex()];
            return true;
        }

        void toBytes(byte bytes[], int from_index) const
        {
            bytes[from_index] = value_;
        };

        void setValue(const byte& value) { value_ = value; }
        byte getValue() const { return value_; }

    };
}

#endif //ROBONETTE_SERVER_BYTECELL_H
