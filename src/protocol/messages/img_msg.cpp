
#include <robonette/protocol/messages/img_msg.h>

namespace rbnt
{
    ImgMsg::ImgMsg() :  tag_(INDX_TAG),
                        encoding_(INDX_ENCODING),
                        height_(INDX_HEIGHT),
                        width_(INDX_WIDTH),
                        step_(INDX_STEP),
                        is_bigendian_(INDX_BIGENDIAN){}


    bool ImgMsg::toBytes(byte *bytes, size_t size)
    {
        const size_t my_size = ImgMsg::FIELDS_SIZE +
                               (step_.getValue() * height_.getValue());
        if (size != my_size)
            return false;

        tag_.toBytes(bytes);
        encoding_.toBytes(bytes);
        height_.toBytes(bytes);
        width_.toBytes(bytes);
        step_.toBytes(bytes);
        is_bigendian_.toBytes(bytes);

        //TODO: FIX PROBLEM HERE
        for (int indx = INDX_DATA; indx < size; indx++)
            bytes[indx] = data_[indx - INDX_DATA];

        return true;
    }
}