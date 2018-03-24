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

        void setValue(float value) { value_ = value; }

    };
}

#endif //ROBONETTE_SERVER_FLOAT32_CELL_H
