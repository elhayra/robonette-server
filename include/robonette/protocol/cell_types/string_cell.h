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
            memcpy(&value_, bytes + getIndex(), SIZE);
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
