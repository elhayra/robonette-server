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


#include <robonette/protocol/messages/img_msg.h>

namespace rbnt
{
    ImgMsg::ImgMsg() :  tag_(INDX_TAG),
                        encoding_(INDX_ENCODING),
                        height_(INDX_HEIGHT),
                        width_(INDX_WIDTH),
                        step_(INDX_STEP),
                        is_bigendian_(INDX_BIGENDIAN){}


    bool ImgMsg::toBytes(uint8_t *bytes, size_t size)
    {
        // data is empty or not match height*step
        if (!data_->size() ||
            (data_->size() != height_.getValue() * step_.getValue()))
            return false;
        if (size != getSize())
            return false;

        tag_.toBytes(bytes);
        encoding_.toBytes(bytes);
        height_.toBytes(bytes);
        width_.toBytes(bytes);
        step_.toBytes(bytes);
        is_bigendian_.toBytes(bytes);

        for (int indx = INDX_DATA; indx < size; indx++)
            bytes[indx] = data_->at(indx - INDX_DATA);

        return true;
    }
}