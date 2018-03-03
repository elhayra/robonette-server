
#include <ros/ros.h>
#include <manager.h>


int main(int argc, char** argv)
{
    ros::init(argc, argv, "robonette_node");
    ros::NodeHandle nh;

    ROS_INFO("[robonette_node]: starting server");
    Manager manager;
    manager.startServer();

    ROS_INFO("[robonette_node]: waiting for client...");
    manager.waitForClient();

    ROS_INFO("[robonette_node]: got client");

    while (ros::ok())
    {
        manager.loop();
        ros::Duration(1).sleep();
        ros::spinOnce();
    }

    return 0;
}