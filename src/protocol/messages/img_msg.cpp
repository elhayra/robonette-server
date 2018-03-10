
#include <robonette/protocol/messages/img_msg.h>

namespace rbnt
{
    ImgMsg::~ImgMsg()
    {
        deleteData();
    }

    void ImgMsg::setData(const std::vector& data)
    {
        const int size = step_.getValue() * height_.getValue();
        deleteData();
        data_ = new byte[size];
        for (int indx = 0; indx < size; indx++)
            data_[indx] = data[indx];
    }

    bool ImgMsg::toBytes(byte *bytes, size_t size) const
    {
        const int msg_size = RbntMsg::SIZE +
                             (StringCell::SIZE * 2) +
                             (UInt32Cell::SIZE * 3) +
                             BoolCell::SIZE +
                             (step_.getValue() * height_.getValue());
        if (size != msg_size)
            return false;

        msg_type_.toBytes(bytes, INDX_MSG_TYPE);
        tag_.toBytes(bytes, INDX_TAG);
        encoding_.toBytes(bytes, INDX_ENCODING);
        height_.toBytes(bytes, INDX_HEIGHT);
        width_.toBytes(bytes, INDX_WIDTH);
        step_.toBytes(bytes, INDX_STEP);
        is_bigendian_.toBytes(bytes, INDX_BIGENDIAN);

        for (int indx = 0; indx < size; indx++)
            bytes[indx + INDX_DATA] = data_[indx];

        return true;
    }

    void ImgMsg::deleteData()
    {
        if (data_ != nullptr)
        {
            delete [] data_;
            data_ = nullptr;
        }
    }
}