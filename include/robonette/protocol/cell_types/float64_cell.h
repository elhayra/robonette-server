

#ifndef ROBONETTE_SERVER_FLOAT64_CELL_H
#define ROBONETTE_SERVER_FLOAT64_CELL_H

#include "packet_cell.h"

namespace rbnt
{
    class Float64Cell : public PacketCell
    {
    private:
        double value_ = 0;
    public:
        static const int SIZE = 8;
        Float64Cell(int index, double value) : PacketCell(index) { setValue(value); }
        Float64Cell(int index) : PacketCell(index) {}
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

        void setValue(double value) { value_ = value; }

    };
}
#endif //ROBONETTE_SERVER_FLOAT64_CELL_H
