
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
        const uint8_t *data_ = nullptr;

        void deleteData();

    public:
        static const int FIELDS_SIZE = (StringCell::SIZE * 2) +
                (Int32Cell::SIZE * 3) + BoolCell::SIZE;

        static const int INDX_TAG = 0;
        static const int INDX_ENCODING = INDX_TAG + StringCell::SIZE;
        static const int INDX_HEIGHT = INDX_ENCODING + StringCell::SIZE;
        static const int INDX_WIDTH = INDX_HEIGHT + Int32Cell::SIZE;
        static const int INDX_STEP = INDX_WIDTH + Int32Cell::SIZE;
        static const int INDX_BIGENDIAN = INDX_STEP + Int32Cell::SIZE;
        static const int INDX_DATA = INDX_BIGENDIAN + BoolCell::SIZE;

        ImgMsg();

        bool toBytes(byte bytes[], size_t size);
        void setTag(const std::string &value) { tag_.setValue(value); }
        void setEncoding(const std::string &value) { encoding_.setValue(value); }
        void setHeight(uint32_t value) { height_.setValue(value); }
        void setWidth(uint32_t value) { width_.setValue(value); }
        void setStep(uint32_t value) { step_.setValue(value); }
        void isBigEndian(bool value) { is_bigendian_.setValue(value); }
        void setData(const std::vector<uint8_t >& data) { data_ = &data[0]; };
    };
}



#endif //ROBONETTE_IMG_MSG_H
