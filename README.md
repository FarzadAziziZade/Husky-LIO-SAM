# Husky-LIO-SAM
This package is an implementation of the LIO-SAM on Husky UGV in a simulation environmet.

This package is based on:
=========================
  - [LIO-SAM](https://github.com/TixiaoShan/LIO-SAM)
  
  - [HUSKY](https://github.com/husky/husky/tree/3af80eab1ec0b0d44259c6c8797e4a28797507ca)


Requirements:
============
  - [ROS Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)


Make sure that you have installed all dependecies:
==================================================

```
sudo apt-get install -y ros-melodic-navigation
sudo apt-get install -y ros-melodic-robot-localization
sudo apt-get install -y ros-melodic-robot-state-publisher
sudo add-apt-repository ppa:borglab/gtsam-release-4.0
sudo apt install libgtsam-dev libgtsam-unstable-dev
sudo apt-get install ros-melodic-velodyne-*
```

Then install the Husky packages (for more information visit [HUSKY](http://wiki.ros.org/Robots/Husky)):
==============================================================================================

```
sudo apt-get install ros-melodic-husky-*
export HUSKY_GAZEBO_DESCRIPTION=$(rospack find husky_gazebo)/urdf/description.gazebo.xacro
```
  

How to compile:
===============

```
cd ~/catkin_ws_HUSKY_LIO_SAM/src
git clone https://github.com/ChaoqinRobotics/Husky-LIO-SAM.git
cd ..
catkin_make
```

How to run the SLAM Simulation:
===============================
1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam run.launch
3. roslaunch lio_sam mrun.launch



How to run the merging module without SLAM:
===========================================
1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam mrun_wrviz.launch
