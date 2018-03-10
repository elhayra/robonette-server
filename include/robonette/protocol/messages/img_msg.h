
#ifndef ROBONETTE_IMG_MSG_H
#define ROBONETTE_IMG_MSG_H

#include <robonette/protocol/messages/rbnt_msg.h>
#include <robonette/protocol/cell_types/uint32_cell.h>
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
        UInt32Cell height_;
        UInt32Cell width_;
        UInt32Cell step_;
        BoolCell is_bigendian_;
        byte *data_ = nullptr;

        void deleteData();

    public:

        static const int INDX_TAG = INDX_MSG_TYPE + ByteCell::SIZE;
        static const int INDX_ENCODING = INDX_TAG + StringCell::SIZE;
        static const int INDX_HEIGHT = INDX_ENCODING + StringCell::SIZE;
        static const int INDX_WIDTH = INDX_HEIGHT + UInt32Cell::SIZE;
        static const int INDX_STEP = INDX_WIDTH + UInt32Cell::SIZE;
        static const int INDX_BIGENDIAN = INDX_STEP + UInt32Cell::SIZE;
        static const int INDX_DATA = INDX_BIGENDIAN + BoolCell::SIZE;

        ~ImgMsg();

        bool toBytes(byte bytes[], size_t size) const;
        void setTag(const std::string &value) { tag_.setValue(value); }
        void setEncoding(const std::string &value) { tag_.setValue(value); }
        void setHeight(uint32_t value) { height_.setValue(value); }
        void setWidth(uint32_t value) { width_.setValue(value); }
        void setStep(uint32_t value) { step_.setValue(value); }
        void isBigEndian(bool value) { is_bigendian_.setValue(value); }
        void setData(const std::vector& data);

    };
}



#endif //ROBONETTE_IMG_MSG_H
