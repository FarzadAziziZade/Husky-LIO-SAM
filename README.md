# Husky-LIO-SAM
Husky-LIO-SAM

This package is based on:

  1-(https://github.com/TixiaoShan/LIO-SAM)
  
  2-(https://github.com/husky/husky/tree/3af80eab1ec0b0d44259c6c8797e4a28797507ca)


Make sure that you have installed all dependecies:

  1-sudo apt-get install -y ros-kinetic-navigation
  
  2-sudo apt-get install -y ros-kinetic-robot-localization
  
  3-sudo apt-get install -y ros-kinetic-robot-state-publisher
  
  4-sudo add-apt-repository ppa:borglab/gtsam-release-4.0
  
  5-sudo apt install libgtsam-dev libgtsam-unstable-dev
  

Then install the Husky packages (for more information visit http://wiki.ros.org/Robots/Husky):

  1-sudo apt-get install ros-melodic-husky-simulator ros-melodic-husky-navigation ros-melodic-husky-gazebo ros-melodic-husky-viz
  
  2-export HUSKY_GAZEBO_DESCRIPTION=$(rospack find husky_gazebo)/urdf/description.gazebo.xacro
  

How to run the SLAM Simulation:

1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam run.launch
3. roslaunch lio_sam mrun.launch



How to run the merging module without SLAM:

1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam mrun_wrviz.launch
