

#ifndef ROBONETTE_SERVER_INFOMSG_H
#define ROBONETTE_SERVER_INFOMSG_H

#include <protocol/cell_types/byte_cell.h>
#include <protocol/cell_types/string_cell.h>
#include <protocol/cell_types/int32_cell.h>
#include <protocol/cell_types/float32_cell.h>
#include <protocol/cell_types/float64_cell.h>
#include <protocol/cell_types/bool_cell.h>
#include <tcp_server.h>


class InfoMsg
{
private:
    ByteCell data_type_;
    StringCell data_tag_;
    StringCell data_units_;


    Int32Cell data_int_;
    Float32Cell data_float32_;
    Float64Cell data_float64_;
    ByteCell data_byte_;
    BoolCell data_bool_;
    StringCell data_string_;

public:

    static const int DATA_SIZE = 8;
    static const int SIZE = 49;
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

    InfoMsg() : data_type_(INDX_DATA_TYPE),
                data_tag_(INDX_DATA_TAG),
                data_units_(INDX_DATA_UNITS),
                data_int_(INDX_DATA),
                data_float32_(INDX_DATA),
                data_float64_(INDX_DATA),
                data_byte_(INDX_DATA),
                data_bool_(INDX_DATA),
                data_string_(INDX_DATA)
    {

    }

    void setDataType(DataType value) { data_type_.setValue((byte)value); }
    void setDataTag(std::string value) { data_tag_.setValue(value); }
    void setDataUnits(std::string value) { data_units_.setValue(value); }

    void setDataInt32(int32_t value) { data_int_.setValue(value); }
    void setDataFloat32(float value) { data_float32_.setValue(value); }
    void setDataFloat64(double value) { data_float64_.setValue(value); }
    void setDataByte(byte value) { data_byte_.setValue(value); }
    void setDataBool(bool value) { data_bool_.setValue(value); }
    void setDataString(std::string value) { data_string_.setValue(value); }

    bool toBytes(byte bytes[], size_t size)
    {
        if (size != SIZE)
            return false;
        for (int i=0; i<SIZE; i++)
            bytes[i] = 0;

        data_type_.toBytes(bytes, INDX_DATA_TYPE);
        data_tag_.toBytes(bytes, INDX_DATA_TAG);
        data_units_.toBytes(bytes, INDX_DATA_UNITS);
        switch (byteToDataType(data_type_.getValue()))
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

    DataType byteToDataType(byte byte_in)
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

};

#endif //ROBONETTE_SERVER_INFOMSG_H
