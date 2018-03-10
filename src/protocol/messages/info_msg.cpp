
#include <robonette/protocol/messages/info_msg.h>

namespace rbnt
{
    InfoMsg::InfoMsg() : type_(INDX_DATA_TYPE),
                        tag_(INDX_DATA_TAG),
                        units_(INDX_DATA_UNITS),
                        data_int_(INDX_DATA),
                        data_float32_(INDX_DATA),
                        data_float64_(INDX_DATA),
                        data_byte_(INDX_DATA),
                        data_bool_(INDX_DATA),
                        data_string_(INDX_DATA) {}


    bool InfoMsg::toBytes(byte bytes[], size_t size) const
    {
        if (size != SIZE)
            return false;
        for (int i=0; i<SIZE; i++)
            bytes[i] = 0;

        msg_type_.toBytes(bytes, INDX_MSG_TYPE);
        type_.toBytes(bytes, INDX_DATA_TYPE);
        tag_.toBytes(bytes, INDX_DATA_TAG);
        units_.toBytes(bytes, INDX_DATA_UNITS);
        switch (byteToDataType(type_.getValue()))
        {
            case DataType::INT32:
            {
                data_int_.toBytes(bytes, INDX_DATA);
                break;
            }
            case DataType::FLOAT32:
            {
                data_float32_.toBytes(bytes, INDX_DATA);
                break;
            }
            case DataType::FLOAT64:
            {
                data_float64_.toBytes(bytes, INDX_DATA);
                break;
            }
            case DataType::BYTE:
            {
                data_byte_.toBytes(bytes, INDX_DATA);
                break;
            }
            case DataType::BOOL:
            {
                data_bool_.toBytes(bytes, INDX_DATA);
                break;
            }
            case DataType::STRING:
            {
                data_string_.toBytes(bytes, INDX_DATA);
                break;
            }
        }
        return true;
    }

    InfoMsg::DataType InfoMsg::byteToDataType(byte byte_in) const
    {
        switch(byte_in)
        {
            case 1:
                return DataType::INT32;
            case 2:
                return DataType::FLOAT32;
            case 3:
                return DataType::FLOAT64;
            case 4:
                return DataType::BYTE;
            case 5:
                return DataType::BOOL;
            case 6:
                return DataType::STRING;
        }
        return DataType::INVALID;
    }

}