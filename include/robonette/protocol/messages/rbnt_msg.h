

#ifndef ROBONETTE_RBNT_MSG_H
#define ROBONETTE_RBNT_MSG_H

#include <robonette/tcp_server.h>
#include <robonette/protocol/cell_types/byte_cell.h>

namespace rbnt
{
    class RbntMsg
    {

    protected:
        ByteCell msg_type;

    public:
        enum class MsgType
        {
            INFO = 1,
            IMAGE = 2,
            MAP = 3,
            COMMAND = 4
        };

        static const uint8_t INDX_MSG_TYPE = 0;
        virtual bool toBytes(byte bytes[], size_t size) const = 0;

        RbntMsg() : msg_type(INDX_MSG_TYPE) {};

    };
}


#endif //ROBONETTE_RBNT_MSG_H
