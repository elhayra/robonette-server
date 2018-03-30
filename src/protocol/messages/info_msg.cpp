/*******************************************************************************
* Copyright (c) 2018 Elhay Rauper
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*     * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
*     * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/


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
                        data_string_(INDX_DATA){}


    bool InfoMsg::toBytes(uint8_t bytes[], size_t size)
    {
        if (size != SIZE)
            return false;
        for (int i=0; i<SIZE; i++)
            bytes[i] = 0;

        type_.toBytes(bytes);
        tag_.toBytes(bytes);
        units_.toBytes(bytes);

        switch (byteToDataType(type_.getValue()))
        {
            case DataType::INT32:
            {
                data_int_.toBytes(bytes);
                break;
            }
            case DataType::FLOAT32:
            {
                data_float32_.toBytes(bytes);
                break;
            }
            case DataType::FLOAT64:
            {
                data_float64_.toBytes(bytes);
                break;
            }
            case DataType::BYTE:
            {
                data_byte_.toBytes(bytes);
                break;
            }
            case DataType::BOOL:
            {
                data_bool_.toBytes(bytes);
                break;
            }
            case DataType::STRING:
            {
                data_string_.toBytes(bytes);
                break;
            }
        }
        return true;
    }

    InfoMsg::DataType InfoMsg::byteToDataType(uint8_t byte_in) const
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