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

#ifndef ROBONETTE_RBNT_HEADER_H
#define ROBONETTE_RBNT_HEADER_H

#include "rbnt_msg.h"
#include "robonette/protocol/cell_types/byte_cell.h"
#include "robonette/protocol/cell_types/int32_cell.h"

namespace rbnt
{
    class RbntHeader : public RbntMsg
    {
    private:
        Int32Cell header_start;
        ByteCell msg_type;
        Int32Cell msg_size;

    public:

        static const int INDX_HEADER_START = 0;
        static const int INDX_MSG_TYPE = INDX_HEADER_START + Int32Cell::SIZE;
        static const int INDX_MSG_SIZE = INDX_MSG_TYPE + ByteCell::SIZE;

        static const int SIZE = (Int32Cell::SIZE * 2) + ByteCell::SIZE;
        static const int VALID_HEADER_START = 0x01;

        enum class MsgType
        {
            HEADER =            1,
            INFO =              2,
            IMAGE =             3,
            COMPRESSED_IMAGE =  4,
            MAP =               5,
            COMMAND =           6
        };

        RbntHeader() : header_start(INDX_HEADER_START),
                       msg_type(INDX_MSG_TYPE),
                       msg_size(INDX_MSG_SIZE) {}

        MsgType getMsgType() { return (MsgType)msg_type.getValue(); }
        int32_t getMsgSize() { return msg_size.getValue(); }

        void setHeaderStart(uint32_t value) { header_start.setValue(value); }
        void setMsgType(MsgType type) { msg_type.setValue((int)type); }
        void setMsgSize(uint32_t size) { msg_size.setValue(size); }

        bool toBytes(uint8_t bytes[], size_t size)
        {
            if (size != SIZE)
                return false;

            header_start.toBytes(bytes);
            msg_type.toBytes(bytes);
            msg_size.toBytes(bytes);

            if (header_start.getValue() != VALID_HEADER_START)
                return false;
            return true;
        }
    };
}

#endif //ROBONETTE_RBNT_HEADER_H
