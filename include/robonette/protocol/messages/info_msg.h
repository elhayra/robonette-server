
#ifndef ROBONETTE_INFO_MSG_H
#define ROBONETTE_INFO_MSG_H

#include <robonette/protocol/cell_types/byte_cell.h>
#include <robonette/protocol/cell_types/string_cell.h>
#include <robonette/protocol/cell_types/int32_cell.h>
#include <robonette/protocol/cell_types/float32_cell.h>
#include <robonette/protocol/cell_types/float64_cell.h>
#include <robonette/protocol/cell_types/bool_cell.h>
#include <robonette/tcp_server.h>
#include <robonette/protocol/messages/rbnt_msg.h>

namespace rbnt
{
    class InfoMsg : RbntMsg
    {
    private:
        ByteCell type_;
        StringCell tag_;
        StringCell units_;

        Int32Cell data_int_;
        Float32Cell data_float32_;
        Float64Cell data_float64_;
        ByteCell data_byte_;
        BoolCell data_bool_;
        StringCell data_string_;

    public:

        static const int DATA_SIZE = 8;
        static const int SIZE = ByteCell::SIZE + (StringCell::SIZE * 2) + DATA_SIZE;

        static const int INDX_DATA_TYPE = 0;
        static const int INDX_DATA_TAG = INDX_DATA_TYPE + ByteCell::SIZE;
        static const int INDX_DATA_UNITS = INDX_DATA_TAG + StringCell::SIZE;
        static const int INDX_DATA = INDX_DATA_UNITS + StringCell::SIZE;


        enum class DataType
        {
            INT32 = 1,
            FLOAT32 = 2,
            FLOAT64 = 3,
            BYTE = 4,
            BOOL = 5,
            STRING = 6,
            INVALID = 7
        };

        InfoMsg();

        void setDataType(const DataType &value) { type_.setValue((uint8_t)value); }
        void setDataTag(const std::string &value) { tag_.setValue(value); }
        void setDataUnits(const std::string &value) { units_.setValue(value); }

        void setDataInt32(const int32_t &value) { data_int_.setValue(value); }
        void setDataFloat32(const float &value) { data_float32_.setValue(value); }
        void setDataFloat64(const double &value) { data_float64_.setValue(value); }
        void setDataByte(const uint8_t &value) { data_byte_.setValue(value); }
        void setDataBool(const bool &value) { data_bool_.setValue(value); }
        void setDataString(const std::string &value) { data_string_.setValue(value); }

        bool toBytes(uint8_t bytes[], size_t size);
        DataType byteToDataType(uint8_t byte_in) const;
    };
}

#endif //ROBONETTE_INFO_MSG_H
