
#include <robonette/protocol/messages/compressed_img_msg.h>

namespace rbnt
{
    CompressedImgMsg::CompressedImgMsg() :  tag_(INDX_TAG),
                                            format_(INDX_FORMAT),
                                            img_size_(INDX_IMG_SIZE){}

    bool CompressedImgMsg::toBytes(uint8_t *bytes, size_t size)
    {
        // data is empty
        if (!data_->size())
            return false;
        if (size != getSize())
            return false;

        tag_.toBytes(bytes);
        format_.toBytes(bytes);
        img_size_.toBytes(bytes);

        for (int indx = INDX_DATA; indx < size; indx++)
            bytes[indx] = data_->at(indx - INDX_DATA);
        return true;
    }
}