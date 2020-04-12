// Generated by gencpp from file hector_nav_msgs/GetRobotTrajectory.msg
// DO NOT EDIT!


#ifndef HECTOR_NAV_MSGS_MESSAGE_GETROBOTTRAJECTORY_H
#define HECTOR_NAV_MSGS_MESSAGE_GETROBOTTRAJECTORY_H

#include <ros/service_traits.h>


#include <hector_nav_msgs/GetRobotTrajectoryRequest.h>
#include <hector_nav_msgs/GetRobotTrajectoryResponse.h>


namespace hector_nav_msgs
{

struct GetRobotTrajectory
{

typedef GetRobotTrajectoryRequest Request;
typedef GetRobotTrajectoryResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct GetRobotTrajectory
} // namespace hector_nav_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::hector_nav_msgs::GetRobotTrajectory > {
  static const char* value()
  {
    return "c7bd40129c5786fc26351edbd33b8d33";
  }

  static const char* value(const ::hector_nav_msgs::GetRobotTrajectory&) { return value(); }
};

template<>
struct DataType< ::hector_nav_msgs::GetRobotTrajectory > {
  static const char* value()
  {
    return "hector_nav_msgs/GetRobotTrajectory";
  }

  static const char* value(const ::hector_nav_msgs::GetRobotTrajectory&) { return value(); }
};


// service_traits::MD5Sum< ::hector_nav_msgs::GetRobotTrajectoryRequest> should match 
// service_traits::MD5Sum< ::hector_nav_msgs::GetRobotTrajectory > 
template<>
struct MD5Sum< ::hector_nav_msgs::GetRobotTrajectoryRequest>
{
  static const char* value()
  {
    return MD5Sum< ::hector_nav_msgs::GetRobotTrajectory >::value();
  }
  static const char* value(const ::hector_nav_msgs::GetRobotTrajectoryRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::hector_nav_msgs::GetRobotTrajectoryRequest> should match 
// service_traits::DataType< ::hector_nav_msgs::GetRobotTrajectory > 
template<>
struct DataType< ::hector_nav_msgs::GetRobotTrajectoryRequest>
{
  static const char* value()
  {
    return DataType< ::hector_nav_msgs::GetRobotTrajectory >::value();
  }
  static const char* value(const ::hector_nav_msgs::GetRobotTrajectoryRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::hector_nav_msgs::GetRobotTrajectoryResponse> should match 
// service_traits::MD5Sum< ::hector_nav_msgs::GetRobotTrajectory > 
template<>
struct MD5Sum< ::hector_nav_msgs::GetRobotTrajectoryResponse>
{
  static const char* value()
  {
    return MD5Sum< ::hector_nav_msgs::GetRobotTrajectory >::value();
  }
  static const char* value(const ::hector_nav_msgs::GetRobotTrajectoryResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::hector_nav_msgs::GetRobotTrajectoryResponse> should match 
// service_traits::DataType< ::hector_nav_msgs::GetRobotTrajectory > 
template<>
struct DataType< ::hector_nav_msgs::GetRobotTrajectoryResponse>
{
  static const char* value()
  {
    return DataType< ::hector_nav_msgs::GetRobotTrajectory >::value();
  }
  static const char* value(const ::hector_nav_msgs::GetRobotTrajectoryResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // HECTOR_NAV_MSGS_MESSAGE_GETROBOTTRAJECTORY_H
