cmake_minimum_required(VERSION 3.0.2)
project(pcl_m)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin 
find_package(catkin REQUIRED COMPONENTS
  tf
  roscpp
  rospy
  sensor_msgs
  pcl_ros
  cv_bridge
  geometry_msgs
  message_generation
  nav_msgs
  pcl_conversions
  pcl_ros
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
  pcl_conversions
  pcl_ros
  roscpp
  roslint
  sensor_msgs
  std_msgs
  tf
  tf2
  tf2_eigen
  tf2_ros
  velodyne_pointcloud
)

catkin_package(INCLUDE_DIRS include)


find_package(PCL)
find_package(OpenMP REQUIRED)
find_package(PCL REQUIRED QUIET)
find_package(OpenCV REQUIRED QUIET)
find_package(GTSAM REQUIRED QUIET)
find_package(PkgConfig REQUIRED)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
${OpenCV_INCLUDE_DIRS}
  ${GTSAM_INCLUDE_DIR}
)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(
    include
    ${PCL_LIBRARY_DIRS}
  ${OpenCV_LIBRARY_DIRS}
  ${GTSAM_LIBRARY_DIRS}
)
add_definitions(${PCL_DEFINITIONS})

add_executable(node src/node.cpp)

add_dependencies(node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_definitions(${PCL_DEFINITIONS})


target_link_libraries(node
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

# add_executable(feature_extraction src/feature_extraction.cpp)

# add_dependencies(feature_extraction ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# target_link_libraries(feature_extraction
#   ${catkin_LIBRARIES}
#   ${PCL_LIBRARIES}
# )
