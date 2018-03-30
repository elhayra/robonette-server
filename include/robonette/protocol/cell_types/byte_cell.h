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


#ifndef ROBONETTE_SERVER_BYTECELL_H
#define ROBONETTE_SERVER_BYTECELL_H

#include <robonette/protocol/cell_types/packet_cell.h>

namespace rbnt
{
    class ByteCell : public PacketCell
    {
    private:
        uint8_t value_ = 0;
    public:
        static const int SIZE = 1;
        ByteCell(int index, uint8_t value) : PacketCell(index) { setValue(value); }
        ByteCell(int index) : PacketCell(index) {}
        bool fromBytes(const uint8_t bytes[], size_t size)
        {
            if (size < getIndex() + SIZE)
                return false;
            value_ = bytes[getIndex()];
            return true;
        }

        void toBytes(uint8_t bytes[]) const
        {
            bytes[getIndex()] = value_;
        };

        void setValue(const uint8_t& value) { value_ = value; }
        uint8_t getValue() const { return value_; }

    };
}

#endif //ROBONETTE_SERVER_BYTECELL_H
