
#ifndef ROBONETTE_SERVER_INT32_CELL_H
#define ROBONETTE_SERVER_INT32_CELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class Int32Cell : public PacketCell
    {
    private:
        int32_t value_ = 0;
    public:
        static const int SIZE = 4;
        Int32Cell(int index, int32_t value) : PacketCell(index) { setValue(value); }
        Int32Cell(int index) : PacketCell(index) {}
        bool fromBytes(const uint8_t bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            memcpy(&value_, bytes, SIZE);
            return true;
        }

        void toBytes(uint8_t bytes[]) const
        {
            uint8_t *bytes_arr = (uint8_t *)& value_;
            for (int i=0; i<SIZE; i++)
                bytes[i + getIndex()] = bytes_arr[i];
        };

        void setValue(int32_t value) { value_ = value; }
        int32_t getValue() { return value_; }
    };
}
#endif //ROBONETTE_SERVER_INT32_CELL_H
