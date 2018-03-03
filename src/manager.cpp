
#include <manager.h>

void Manager::loop()
{
    byte msg[49] = {/*data type */1,
            /* dataTag */ 104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
            /* dataUnits */104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
            /* data*/0,0,0,0,0,0,0,2 };

    int n = server_.writeBytes(msg, 49);

}

bool Manager::startServer()
{
    server_.bindTo(5005);
    server_.startListen();
    return true;
}

void Manager::waitForClient()
{
    server_.acceptClient();

}