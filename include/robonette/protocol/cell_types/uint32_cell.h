
#ifndef ROBONETTE_UINT32_CELL_H
#define ROBONETTE_UINT32_CELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class UInt32Cell : public PacketCell
    {
    private:
        uint32_t value_ = 0;
    public:
        static const int SIZE = 4;
        UInt32Cell(int index, uint32_t value) : PacketCell(index) { setValue(value); }
        UInt32Cell(int index) : PacketCell(index) {}
        bool fromBytes(const byte bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            memcpy(&value_, bytes, SIZE);
            return true;
        }

        void toBytes(byte bytes[], int from_index) const
        {
            byte *bytes_arr = (byte *)& value_;
            for (int i=0; i<SIZE; i++)
                bytes[i + from_index] = bytes_arr[i];
        };

        uint32_t getValue() const { return value_; }
        void setValue(uint32_t value) { value_ = value; }

    };
}

#endif //ROBONETTE_UINT32_CELL_H
