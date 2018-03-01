#include <ctime>
#include <iostream>
#include <boost/asio.hpp>
#include <ros/ros.h>

using boost::asio::ip::tcp;
using byte = unsigned char;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robonette_server_node");
    ros::NodeHandle nh;
    try
    {
        // Any program that uses asio need to have at least one io_service object
        boost::asio::io_service io_service;

        // acceptor object needs to be created to listen for new connections
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 5005));

        for (;;)
        {
            // creates a socket
            tcp::socket socket(io_service);

            // wait and listen
            acceptor.accept(socket);

            boost::system::error_code ignored_error;

            byte msg[49] = {/*data type */1,
                          /* dataTag */ 104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
                          /* dataUnits */104 ,101 ,108 ,108 ,111, 32, 119, 111, 114 ,108, 100,0,0,0,0,0,0,0,0,0,
                          /* data*/0,0,0,0,0,0,0,2 };

            while (true)
            {
                ros::Duration(1).sleep();
                // writing the message for current time
                boost::asio::write(socket, boost::asio::buffer(msg, 49), ignored_error);

            }

        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}