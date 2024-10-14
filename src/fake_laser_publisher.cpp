// src/fake_laser_publisher.cpp
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <cmath>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "fake_laser_publisher");
    ros::NodeHandle nh;

    ros::Publisher laser_pub = nh.advertise<sensor_msgs::LaserScan>("scan", 50);

    // Configure the LaserScan message
    sensor_msgs::LaserScan scan;
    scan.header.frame_id = "laser_frame";
    scan.angle_min = -M_PI / 2;
    scan.angle_max = M_PI / 2;
    scan.angle_increment = M_PI / 180;
    scan.range_min = 0.1;
    scan.range_max = 10.0;

    int num_readings = (scan.angle_max - scan.angle_min) / scan.angle_increment;
    scan.ranges.resize(num_readings);
    scan.intensities.resize(num_readings);

    ros::Rate rate(10); // 10 Hz

    while (ros::ok())
    {
        // Simulate a simple laser scan (circular object at 1.0 meter distance)
        scan.header.stamp = ros::Time::now();
        for (int i = 0; i < num_readings; ++i)
        {
            scan.ranges[i] = 1.0 + 0.1 * std::sin(i * scan.angle_increment);
            scan.intensities[i] = 1.0;
        }

        laser_pub.publish(scan);
        rate.sleep();
    }

    return 0;
}
