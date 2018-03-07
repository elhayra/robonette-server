

#ifndef ROBONETTE_SERVER_STRINGCELL_H
#define ROBONETTE_SERVER_STRINGCELL_H

#include "packet_cell.h"
#include <iostream>

namespace rbnt
{
    class StringCell : public PacketCell
    {
    private:
        std::string value_;
    public:
        static const int SIZE = 20;
        StringCell(int index, std::string value) : PacketCell(index) { setValue(value); }
        StringCell(int index) : PacketCell(index) {}
        bool fromBytes(byte bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            memcpy(&value_, bytes, SIZE);
            return true;
        }

        void toBytes(byte bytes[], int from_index) const
        {
            char const *bytes_arr = value_.c_str();
            for (int i=0; i<value_.size(); i++)
                bytes[i + from_index] = bytes_arr[i];
        };

        void setValue(std::string value) { value_ = value; }

    };
}

#endif //ROBONETTE_SERVER_STRINGCELL_H
