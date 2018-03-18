

#ifndef ROBONETTE_RBNT_HEADER_H
#define ROBONETTE_RBNT_HEADER_H

#include "rbnt_msg.h"
#include "robonette/protocol/cell_types/byte_cell.h"
#include "robonette/protocol/cell_types/int32_cell.h"

namespace rbnt
{
    class RbntHeader : public RbntMsg
    {
    private:
        Int32Cell header_start;
        ByteCell msg_type;
        Int32Cell msg_size;

    public:

        static const int INDX_HEADER_START = 0;
        static const int INDX_MSG_TYPE = INDX_HEADER_START + Int32Cell::SIZE;
        static const int INDX_MSG_SIZE = INDX_MSG_TYPE + ByteCell::SIZE;

        static const int SIZE = (Int32Cell::SIZE * 2) + ByteCell::SIZE;
        static const int VALID_HEADER_START = 0x01;

        enum class MsgType
        {
            HEADER =    1,
            INFO =      2,
            IMAGE =     3,
            MAP =       4,
            COMMAND =   5
        };

        RbntHeader() : header_start(INDX_HEADER_START),
                       msg_type(INDX_MSG_TYPE),
                       msg_size(INDX_MSG_SIZE) {}

        MsgType getMsgType() { return (MsgType)msg_type.getValue(); }
        int32_t getMsgSize() { return msg_size.getValue(); }

        void setHeaderStart(uint32_t value) { header_start.setValue(value); }
        void setMsgType(MsgType type) { msg_type.setValue((int)type); }
        void setMsgSize(uint32_t size) { msg_size.setValue(size); }

        bool toBytes(byte bytes[], size_t size)
        {
            if (size != SIZE)
                return false;

            header_start.toBytes(bytes);
            msg_type.toBytes(bytes);
            msg_size.toBytes(bytes);

            if (header_start.getValue() != VALID_HEADER_START)
                return false;
            return true;
        }
    };
}

#endif //ROBONETTE_RBNT_HEADER_H
