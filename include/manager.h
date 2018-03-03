
#ifndef ROBONETTE_SERVER_COMM_MANAGER_H
#define ROBONETTE_SERVER_COMM_MANAGER_H

#include <tcp_server.h>

class Manager
{
private:
    TcpServer server_;

public:
    bool startServer();
    void waitForClient();
    void loop();
};


#endif //ROBONETTE_SERVER_COMM_MANAGER_H
