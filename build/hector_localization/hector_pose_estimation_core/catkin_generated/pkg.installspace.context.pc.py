# generated from catkin/cmake/template/pkg.context.pc.in
CATKIN_PACKAGE_PREFIX = ""
PROJECT_PKG_CONFIG_INCLUDE_DIRS = "${prefix}/include;/usr/include/eigen3".split(';') if "${prefix}/include;/usr/include/eigen3" != "" else []
PROJECT_CATKIN_DEPENDS = "rostime;rosconsole;roscpp;sensor_msgs;geometry_msgs;nav_msgs;geographic_msgs;tf".replace(';', ' ')
PKG_CONFIG_LIBRARIES_WITH_PREFIX = "-lhector_pose_estimation".split(';') if "-lhector_pose_estimation" != "" else []
PROJECT_NAME = "hector_pose_estimation_core"
PROJECT_SPACE_DIR = "/home/arslanali/quadrotor-simulation/install"
PROJECT_VERSION = "0.3.0"
