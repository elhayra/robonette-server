
#ifndef ROBONETTE_IMG_MSG_H
#define ROBONETTE_IMG_MSG_H

#include <robonette/protocol/messages/rbnt_msg.h>
#include <robonette/protocol/cell_types/int32_cell.h>
#include <robonette/protocol/cell_types/bool_cell.h>
#include <robonette/protocol/cell_types/string_cell.h>

namespace rbnt
{
    class ImgMsg : RbntMsg
    {
    private:
        StringCell tag;
        Int32Cell height;
        Int32Cell width;
        BoolCell is_bigendian;
        Int32Cell step;
        uint8_t *data;
        //encoding ??? http://docs.ros.org/jade/api/sensor_msgs/html/image__encodings_8h_source.html

    public:
        bool toBytes(byte bytes[], size_t size) const;
        void setDataTag(const std::string &value) { tag.setValue(value); }

    };
}



#endif //ROBONETTE_IMG_MSG_H
