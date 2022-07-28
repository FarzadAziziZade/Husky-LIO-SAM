# Husky-LIO-SAM
This package is an implementation of the LIO-SAM on Husky UGV in a simulation environment.

This package is based on:
=========================
  - [LIO-SAM](https://github.com/TixiaoShan/LIO-SAM)
  
  - [HUSKY](https://github.com/husky/husky/tree/3af80eab1ec0b0d44259c6c8797e4a28797507ca)


Requirements:
============
  - [ROS Melodic](http://wiki.ros.org/melodic/Installation/Ubuntu)


Make sure that you have installed all dependencies:
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
mkdir -p   catkin_ws_HUSKY_LIO_SAM/src
cd ~/catkin_ws_HUSKY_LIO_SAM/src
git clone https://github.com/FarzadAziziZade/Husky-LIO-SAM/H-LIO-SAM.git
git clone https://github.com/FarzadAziziZade/Husky-LIO-SAM/pcl_m.git
cd ..
catkin_make
```

How to prepare simulation environment:
====================================
1. download the [DAE](https://drive.google.com/file/d/1HfOU4oYl1D4UGBcUe0zXGNeuPx7ARpQL/view?usp=sharing) file
2. put the file in (catkin_ws_HUSKY_LIO_SAM/src/H-LIO-SAM/husky/husky_gazebo/worlds/include)
3. go to (catkin_ws_HUSKY_LIO_SAM/src/H-LIO-SAM/husky/husky_gazebo/worlds)
4. open (clearpath_playpen.world) with a texteditor
5. find two lines including (<uri>/home/{USERNAME}/catkin_ws_HUSKY_LIO_SAM/src/H-LIO-SAM/husky/husky_gazebo/worlds/include/minefourthv7withCforGAZEBOO.dae</uri>)
6. replace the {USERNAME}  with your own username
7. save the file and close it

How to run the SLAM simulation:
===============================
1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam run.launch
3. roslaunch lio_sam mrun.launch



How to run the merging module without SLAM:
===========================================
1. roslaunch lio_sam hrun.launch
2. roslaunch lio_sam mrun_wrviz.launch



Results:
========
![Screenshot from 2022-07-28 03-18-07](https://user-images.githubusercontent.com/84402243/181609705-9eeb9cec-36b5-41f8-a9aa-0cf067fc002f.png)
![Screenshot from 2022-07-28 03-18-33](https://user-images.githubusercontent.com/84402243/181609868-ee4055ec-788c-4ea2-82be-8e83fdbd0e26.png)
![Screenshot from 2022-07-28 03-18-11](https://user-images.githubusercontent.com/84402243/181609737-25fd86dc-8f86-4ef5-97cb-5b94663955fb.png)
![Screenshot from 2022-07-28 03-18-14](https://user-images.githubusercontent.com/84402243/181609762-fcaa8b2d-e773-423b-8025-fc97c22f0b0c.png)
![Screenshot from 2022-07-28 03-18-18](https://user-images.githubusercontent.com/84402243/181609835-e47932b5-d29b-4b64-9a11-b208504ed73b.png)
![Screenshot from 2022-07-28 03-18-23](https://user-images.githubusercontent.com/84402243/181609855-f81dddc3-83a3-4f4c-b32e-cb5b1a7812b1.png)

