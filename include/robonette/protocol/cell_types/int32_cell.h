
#ifndef ROBONETTE_SERVER_INT32_CELL_H
#define ROBONETTE_SERVER_INT32_CELL_H

#include "packet_cell.h"

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
        bool fromBytes(byte bytes[], size_t size)
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

        void setValue(int32_t value) { value_ = value; }

    };
}
#endif //ROBONETTE_SERVER_INT32_CELL_H
