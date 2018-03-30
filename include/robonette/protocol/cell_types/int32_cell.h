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


#ifndef ROBONETTE_SERVER_INT32_CELL_H
#define ROBONETTE_SERVER_INT32_CELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class Int32Cell : public PacketCell
    {
    private:
        int32_t value_ = 0;
    public:
        static const int SIZE = 4;
        Int32Cell(int index, int32_t value) : PacketCell(index) { setValue(value); }
        Int32Cell(int index) : PacketCell(index) {}
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

        void setValue(int32_t value) { value_ = value; }
        int32_t getValue() { return value_; }
    };
}
#endif //ROBONETTE_SERVER_INT32_CELL_H
