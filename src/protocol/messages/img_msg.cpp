
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