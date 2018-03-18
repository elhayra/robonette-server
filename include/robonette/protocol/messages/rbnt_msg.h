

#ifndef ROBONETTE_RBNT_MSG_H
#define ROBONETTE_RBNT_MSG_H

#include <robonette/tcp_server.h>

namespace rbnt
{
    class RbntMsg
    {
        virtual bool toBytes(byte bytes[], size_t size) = 0;
    };
}


#endif //ROBONETTE_RBNT_MSG_H
