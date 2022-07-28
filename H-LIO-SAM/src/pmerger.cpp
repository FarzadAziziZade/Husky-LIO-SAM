#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <velodyne_pointcloud/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>
#include <pcl_ros/transforms.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;
    ros::Publisher cloud_pub_;
    tf::TransformListener tf_listener_;
    std::string output_frame_id_;
    pcl::PointCloud<pcl::PointXYZ> cloud_src_1;
    pcl::PointCloud<pcl::PointXYZ> cloud_src_2;
    pcl::PointCloud<pcl::PointXYZ> cloud_src_3;
    pcl::PointCloud<pcl::PointXYZ> cloud_src_4;
    pcl::PointCloud<pcl::PointXYZ> final_cloud_src;
    pcl::PointCloud<pcl::PointXYZ> final_cloud_src_2;
    pcl::PointCloud<pcl::PointXYZ> final_cloud_src_3;
    cloud_pub_ = n.advertise<sensor_msgs::PointCloud2>("concatenated_cloud", 1);
    ros::Duration duration = ros::Duration(1.0 / 20.0);
    ros::Rate loop_r(duration);
    sensor_msgs::PointCloud2 cloud_1;
    sensor_msgs::PointCloud2 cloud_2;
    sensor_msgs::PointCloud2 cloud_3;
    sensor_msgs::PointCloud2 cloud_4;
    sensor_msgs::PointCloud2 concatenated_cloud;

    while (ros::ok)
    {
        boost::shared_ptr<sensor_msgs::PointCloud2 const> sharedPtr;
        sharedPtr = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/velodyne_points",ros::Duration(1));
        if (sharedPtr == NULL)
            ROS_INFO("No Pointcloud receieved");
        else
            cloud_1 = *sharedPtr;
        sharedPtr = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/velodyne_points_front/velodyne_points",ros::Duration(1));
        if (sharedPtr == NULL)
            ROS_INFO("No Pointcloud_2 receieved");
        else
            cloud_2 = *sharedPtr;
        
                sharedPtr = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/velodyne_points_rear/velodyne_points",ros::Duration(1));
        if (sharedPtr == NULL)
            ROS_INFO("No Pointcloud_2 receieved");
        else
            cloud_3 = *sharedPtr;

                sharedPtr = ros::topic::waitForMessage<sensor_msgs::PointCloud2>("/velodyne_points_roof/velodyne_points",ros::Duration(1));
        if (sharedPtr == NULL)
            ROS_INFO("No Pointcloud_2 receieved");
        else
            cloud_4 = *sharedPtr;

        tf_listener_.waitForTransform("base_link", "velodyne", ros::Time(0), ros::Duration(1.0));


        pcl::PCLPointCloud2 pcl_pc2;
        pcl_conversions::toPCL(cloud_1, pcl_pc2);
        pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromPCLPointCloud2(pcl_pc2, *temp_cloud);
        cloud_src_1 = *temp_cloud;

        pcl::PCLPointCloud2 pcl_2_pc2_2;
        pcl_conversions::toPCL(cloud_2, pcl_2_pc2_2);
        pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud_2(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromPCLPointCloud2(pcl_2_pc2_2, *temp_cloud_2);
        cloud_src_2 = *temp_cloud_2;


        pcl::PCLPointCloud2 pcl_2_pc2_3;
        pcl_conversions::toPCL(cloud_3, pcl_2_pc2_3);
        pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud_3(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromPCLPointCloud2(pcl_2_pc2_3, *temp_cloud_3);
        cloud_src_3 = *temp_cloud_3;


        pcl::PCLPointCloud2 pcl_2_pc2_4;
        pcl_conversions::toPCL(cloud_4, pcl_2_pc2_4);
        pcl::PointCloud<pcl::PointXYZ>::Ptr temp_cloud_4(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::fromPCLPointCloud2(pcl_2_pc2_4, *temp_cloud_4);
        cloud_src_4 = *temp_cloud_4;


        pcl::PointCloud<pcl::PointXYZ> pc_transformed_1;
        pcl::PointCloud<pcl::PointXYZ> pc_transformed_2;
        pcl::PointCloud<pcl::PointXYZ> pc_transformed_3;
        pcl::PointCloud<pcl::PointXYZ> pc_transformed_4;
        pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_transformed_1(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_transformed_2(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_transformed_3(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_transformed_4(new pcl::PointCloud<pcl::PointXYZ>);



        float theta_1 = 0;
        float theta_2 = -1.05;
        float theta_3 = 1.05;
        float theta_4 = 1.57;


        Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();
        transform_1.translation() << 0, 0.0, 0.5;
        transform_1.rotate(Eigen::AngleAxisf(theta_1, Eigen::Vector3f::UnitY()));

        Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
        transform_2.translation() << -0.3, 0.0, 0.7;
        transform_2.rotate(Eigen::AngleAxisf(theta_2, Eigen::Vector3f::UnitY()));

        Eigen::Affine3f transform_3 = Eigen::Affine3f::Identity();
        transform_3.translation() << 0.3, 0.0, 0.7;
        transform_3.rotate(Eigen::AngleAxisf(theta_3, Eigen::Vector3f::UnitY()));

        Eigen::Affine3f transform_4 = Eigen::Affine3f::Identity();
        transform_4.translation() << -0.03, 0.0, 0.85;
        transform_4.rotate(Eigen::AngleAxisf(theta_4, Eigen::Vector3f::UnitY()));
        
        pcl::transformPointCloud(cloud_src_1, *ptr_transformed_1, transform_1);
        pcl::transformPointCloud(cloud_src_2, *ptr_transformed_2, transform_2);
        pcl::transformPointCloud(cloud_src_3, *ptr_transformed_3, transform_3);
        pcl::transformPointCloud(cloud_src_4, *ptr_transformed_4, transform_4);
        pc_transformed_1 = *ptr_transformed_1;
        pc_transformed_2 = *ptr_transformed_2;
        pc_transformed_3 = *ptr_transformed_3;
        pc_transformed_4 = *ptr_transformed_4;

        final_cloud_src = pc_transformed_1 + pc_transformed_2;
        final_cloud_src_2 = pc_transformed_3 + pc_transformed_4;
        final_cloud_src_3 = final_cloud_src_2 + final_cloud_src;

        final_cloud_src_3.header.frame_id = "base_link";
        cloud_pub_.publish(final_cloud_src_3);


    }
}
