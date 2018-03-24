

#ifndef ROBONETTE_SERVER_STRINGCELL_H
#define ROBONETTE_SERVER_STRINGCELL_H

#include <iostream>
#include <robonette/protocol/cell_types/packet_cell.h>

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
        bool fromBytes(const uint8_t bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            memcpy(&value_, bytes, SIZE);
            return true;
        }

        void toBytes(uint8_t bytes[]) const
        {
            char const *bytes_arr = value_.c_str();
            for (int i=0; i<value_.size(); i++)
                bytes[i + getIndex()] = bytes_arr[i];
        };

        void setValue(const std::string& value) { value_ = value; }
    };
}

#endif //ROBONETTE_SERVER_STRINGCELL_H
