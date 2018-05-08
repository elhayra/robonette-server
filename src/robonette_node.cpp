/*******************************************************************************
* Copyright (c) 2018 Elhay Rauper
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*     * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
*     * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/


#include <ros/ros.h>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/Range.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>
#include <nav_msgs/OccupancyGrid.h>
#include <robonette/manager.h>

rbnt::Manager manager;

void battCB(const sensor_msgs::BatteryState::ConstPtr &msg)
{
    int32_t batt_lvl = (int32_t)msg->percentage;
    if (manager.isClientConnected())
        manager.writeInfo("Battery", batt_lvl, "%");
}

void urfCB(const sensor_msgs::Range::ConstPtr &msg)
{
    float sensor_lvl = msg->range;
    if (manager.isClientConnected())
        manager.writeInfo("Ultrasonic", sensor_lvl, "meters");
}

void kinectCB(const sensor_msgs::Image::ConstPtr &msg)
{
    //ROS_INFO("encoding: %s", msg->encoding.c_str());
    //ROS_INFO("width: %i", msg->width);
    //ROS_INFO("height: %i", msg->height);
    //ROS_INFO("steps: %i", msg->step);
    //ROS_INFO("bigendian: %s",(msg->is_bigendian? "true" : "false"));
    if (manager.isClientConnected())
        manager.writeImg("Kinect", msg);
}

void kinectCompressedCB(const sensor_msgs::CompressedImage::ConstPtr &msg)
{
    ROS_INFO("encoding: %s", msg->format.c_str());
    if (manager.isClientConnected())
        manager.writeImg("Kinect", msg);
}

void mapCB(const nav_msgs::OccupancyGrid::ConstPtr &msg)
{
    fprintf(stderr, "got map msg\n");
    fprintf(stderr, "server is %i\n", manager.isServerOpen());
    //if (manager.isClientConnected())
    //      manager.writeMap(msg);
}

void startServer()
{
    ROS_INFO("[robonette_node]: starting server");
    manager.startServer();
}

void waitForClient()
{
    ROS_INFO("[robonette_node]: waiting for client...");
    manager.waitForClient();
    ROS_INFO("[robonette_node]: got client");
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robonette_node");
    ros::NodeHandle nh;

    ros::Subscriber batt_sub = nh.subscribe("battery", 5, battCB);
    ros::Subscriber urf_sub = nh.subscribe("URF/front", 5, urfCB);
    ros::Subscriber kinect_sub = nh.subscribe("/kinect2/qhd/image_color_rect", 5, kinectCB);
    ros::Subscriber kinect_comp_sub = nh.subscribe("/kinect2/qhd/image_color_rect/compressed", 5, kinectCompressedCB);
    ros::Subscriber map_sub = nh.subscribe("/map", 5, mapCB);

    startServer();
    waitForClient();
    ros::AsyncSpinner spinner(4);
    spinner.start();
    while (ros::ok())
    {
        if (!manager.isClientConnected())
        {
            ROS_INFO("client disconnected");
            waitForClient();
        }
        ros::Duration(1).sleep();
    }
    return 0;
}






