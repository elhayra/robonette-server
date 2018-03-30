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

#ifndef ROBONETTE_IMG_MSG_H
#define ROBONETTE_IMG_MSG_H

#include <robonette/protocol/messages/rbnt_msg.h>
#include <robonette/protocol/cell_types/int32_cell.h>
#include <robonette/protocol/cell_types/bool_cell.h>
#include <robonette/protocol/cell_types/string_cell.h>
#include <vector>

namespace rbnt
{
    class ImgMsg : RbntMsg
    {
    private:
        StringCell tag_;
        StringCell encoding_;
        Int32Cell height_;
        Int32Cell width_;
        Int32Cell step_;
        BoolCell is_bigendian_;
        const std::vector<uint8_t > *data_ = nullptr;

        static const int FIELDS_SIZE = (StringCell::SIZE * 2) +
                                       (Int32Cell::SIZE * 3) + BoolCell::SIZE;

    public:

        static const int INDX_TAG = 0;
        static const int INDX_ENCODING = INDX_TAG + StringCell::SIZE;
        static const int INDX_HEIGHT = INDX_ENCODING + StringCell::SIZE;
        static const int INDX_WIDTH = INDX_HEIGHT + Int32Cell::SIZE;
        static const int INDX_STEP = INDX_WIDTH + Int32Cell::SIZE;
        static const int INDX_BIGENDIAN = INDX_STEP + Int32Cell::SIZE;
        static const int INDX_DATA = INDX_BIGENDIAN + BoolCell::SIZE;

        ImgMsg();

        bool toBytes(uint8_t bytes[], size_t size);
        void setTag(const std::string &value) { tag_.setValue(value); }
        void setEncoding(const std::string &value) { encoding_.setValue(value); }
        void setHeight(uint32_t value) { height_.setValue(value); }
        void setWidth(uint32_t value) { width_.setValue(value); }
        void setStep(uint32_t value) { step_.setValue(value); }
        void isBigEndian(bool value) { is_bigendian_.setValue(value); }
        void setData(const std::vector<uint8_t >& data) { data_ = &data; };

        size_t getSize() { data_->size() + FIELDS_SIZE; }
    };
}



#endif //ROBONETTE_IMG_MSG_H
