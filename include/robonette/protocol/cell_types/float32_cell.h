//
// Created by sub on 03/03/18.
//

#ifndef ROBONETTE_SERVER_FLOAT32_CELL_H
#define ROBONETTE_SERVER_FLOAT32_CELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class Float32Cell : public PacketCell
    {
    private:
        float value_ = 0;
    public:
        static const int SIZE = 4;
        Float32Cell(int index, float value) : PacketCell(index) { setValue(value); }
        Float32Cell(int index) : PacketCell(index) {}

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

        void setValue(float value) { value_ = value; }

    };
}

#endif //ROBONETTE_SERVER_FLOAT32_CELL_H
