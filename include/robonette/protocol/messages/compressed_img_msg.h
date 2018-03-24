

#ifndef ROBONETTE_COMPRESSED_IMG_MSG_H
#define ROBONETTE_COMPRESSED_IMG_MSG_H

#include <robonette/protocol/messages/rbnt_msg.h>
#include <robonette/protocol/cell_types/int32_cell.h>
#include <robonette/protocol/cell_types/bool_cell.h>
#include <robonette/protocol/cell_types/string_cell.h>
#include <vector>

namespace rbnt
{
    class CompressedImgMsg : RbntMsg
    {
    private:
        StringCell tag_;
        StringCell format_;
        Int32Cell img_size_;
        const std::vector<uint8_t > *data_ = nullptr;

    public:
        static const int FIELDS_SIZE = (StringCell::SIZE * 2);

        static const int INDX_TAG = 0;
        static const int INDX_FORMAT = INDX_TAG + StringCell::SIZE;
        static const int INDX_IMG_SIZE = INDX_FORMAT + StringCell::SIZE;
        static const int INDX_DATA = INDX_IMG_SIZE + Int32Cell::SIZE;

        CompressedImgMsg();

        bool toBytes(uint8_t bytes[], size_t size);
        void setTag(const std::string &value) { tag_.setValue(value); }
        void setFormat(const std::string &value) { format_.setValue(value); }
        void setImgSize(size_t size) { img_size_.setValue(size); }
        void setData(const std::vector<uint8_t >& data) { data_ = &data; };

        size_t getSize() { data_->size() + FIELDS_SIZE; }
    };
}
#endif //ROBONETTE_COMPRESSED_IMG_MSG_H
