cmake_minimum_required(VERSION 3.0.2)
project(husky_speed_controller)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
geometry_msgs
nav_msgs
roscpp
# rospy
tf
)
#find_package(Boost REQUIRED COMPONENTS system)
#find_package(octomap REQUIRED)
#find_package(gazebo REQUIRED)

# catkin_python_setup()

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES husky_speed_controller
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(
# include
 ${catkin_INCLUDE_DIRS}
)

#add_library(${PROJECT_NAME} src/${PROJECT_NAME}/husky_speed_controller.cpp)
#add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(${PROJECT_NAME}_node src/husky_speed_controller.cpp)
set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})