^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package husky_navigation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.2.7 (2015-12-31)
------------------
* Removed move_base topic remap so it publishes to just cmd_vel to avoid confusion.
* Remapping the move_base topic to be compatible with cpr autonomy core.
* Contributors: Peiyi Chen

0.2.6 (2015-07-08)
------------------

0.2.5 (2015-04-16)
------------------

0.2.4 (2015-04-13)
------------------

0.2.3 (2015-04-08)
------------------
* Increase inflation radius
* Contributors: Paul Bovbel

0.2.2 (2015-03-23)
------------------
* Fix package urls
* Contributors: Paul Bovbel

0.2.1 (2015-03-23)
------------------

0.2.0 (2015-03-23)
------------------

0.1.2 (2015-02-17)
------------------

0.1.1 (2015-01-30)
------------------
* Update web and maintainers
* More meaningful name for mapless navigation demo
* Add missing dependencies
* Contributors: Paul Bovbel

0.1.0 (2015-01-15)
------------------
* Add exploration demo
* Indigo release refactor
* adding prebuilt maps for playpen, slightly more representative map then willowgarage world
* Contributors: Paul Bovbel, Prasenjit Mukherjee

0.0.6 (2013-10-05)
------------------
* Remove attempt to install now gone laser directory.

0.0.5 (2013-10-05)
------------------
* Depend on roslaunch for the check macro.

0.0.4 (2013-10-04)
------------------
* restructuring launch file locations, cleaning out redundant 'laser' folder
* adding dependencies to the package and launch file test in CMake

0.0.3 (2013-10-04)
------------------
* Install the right things.
* Remove urdf folder.

0.0.2 (2013-10-04)
------------------
* cleanup of odom_navigation file and adding tolerance parameters
* removed legacy outdoor navigation demo
* moving param files for odometry navigation around and changed the launchfile to reflect change
* first commit of move_base launch and configuration files in the odom frame
* first commit of catkinized version
