# Husky-LIO-SAM
Husky-LIO-SAM

This package is based on:

(https://github.com/TixiaoShan/LIO-SAM)

(https://github.com/husky/husky/tree/3af80eab1ec0b0d44259c6c8797e4a28797507ca)


Make sure that you have installed all dependecies:

sudo apt-get install -y ros-kinetic-navigation

sudo apt-get install -y ros-kinetic-robot-localization

sudo apt-get install -y ros-kinetic-robot-state-publisher

sudo add-apt-repository ppa:borglab/gtsam-release-4.0

sudo apt install libgtsam-dev libgtsam-unstable-dev


Then install the Husky packages (for more information visit http://wiki.ros.org/Robots/Husky):

sudo apt-get install ros-melodic-husky-simulator ros-melodic-husky-navigation ros-melodic-husky-gazebo ros-melodic-husky-viz

export HUSKY_GAZEBO_DESCRIPTION=$(rospack find husky_gazebo)/urdf/description.gazebo.xacro


How to run the SLAM Simulation:

1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam run.launch
3. roslaunch lio_sam mrun.launch



How to run the merging module without SLAM:

1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam mrun_wrviz.launch
