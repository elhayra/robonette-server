
#include <ros/ros.h>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/Image.h>
#include <robonette/manager.h>

rbnt::Manager manager;

void battCB(const sensor_msgs::BatteryState::ConstPtr &msg)
{
    int32_t batt_lvl = (int32_t)msg->percentage;
    manager.writeInfo("Battery", batt_lvl, "%");
}

void urfCB(const sensor_msgs::Range::ConstPtr &msg)
{
    float sensor_lvl = msg->range;
    manager.writeInfo("Ultrasonic", sensor_lvl, "meters");
}

void kinectCB(const sensor_msgs::Image::ConstPtr &msg)
{
    ROS_INFO("encoding: %s", msg->encoding.c_str());
    ROS_INFO("width: %i", msg->width);
    ROS_INFO("height: %i", msg->height);
    ROS_INFO("steps: %i", msg->step);
    ROS_INFO("bigendian: %s",(msg->is_bigendian? "true" : "false"));
    manager.writeImg("Kinect", msg);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "robonette_node");
    ros::NodeHandle nh;

    ROS_INFO("[robonette_node]: starting server");

    //manager.startServer();

    ROS_INFO("[robonette_node]: waiting for client...");
    //manager.waitForClient();

    ROS_INFO("[robonette_node]: got client");

    ros::Subscriber batt_sub = nh.subscribe("battery", 5, battCB);
    ros::Subscriber urf_sub = nh.subscribe("URF/front", 5, urfCB);
    ros::Subscriber kinect_sub = nh.subscribe("/kinect2/qhd/image_color_rect", 5, kinectCB);


    while (ros::ok())
    {
        manager.loop();
        ros::Duration(1).sleep();
        ros::spinOnce();
    }

    return 0;
}






