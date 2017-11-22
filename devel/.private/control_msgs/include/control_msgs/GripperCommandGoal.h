// Generated by gencpp from file control_msgs/GripperCommandGoal.msg
// DO NOT EDIT!


#ifndef CONTROL_MSGS_MESSAGE_GRIPPERCOMMANDGOAL_H
#define CONTROL_MSGS_MESSAGE_GRIPPERCOMMANDGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <control_msgs/GripperCommand.h>

namespace control_msgs
{
template <class ContainerAllocator>
struct GripperCommandGoal_
{
  typedef GripperCommandGoal_<ContainerAllocator> Type;

  GripperCommandGoal_()
    : command()  {
    }
  GripperCommandGoal_(const ContainerAllocator& _alloc)
    : command(_alloc)  {
  (void)_alloc;
    }



   typedef  ::control_msgs::GripperCommand_<ContainerAllocator>  _command_type;
  _command_type command;




  typedef boost::shared_ptr< ::control_msgs::GripperCommandGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::control_msgs::GripperCommandGoal_<ContainerAllocator> const> ConstPtr;

}; // struct GripperCommandGoal_

typedef ::control_msgs::GripperCommandGoal_<std::allocator<void> > GripperCommandGoal;

typedef boost::shared_ptr< ::control_msgs::GripperCommandGoal > GripperCommandGoalPtr;
typedef boost::shared_ptr< ::control_msgs::GripperCommandGoal const> GripperCommandGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::control_msgs::GripperCommandGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace control_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'control_msgs': ['/home/weety/tart5/devel/.private/control_msgs/share/control_msgs/msg', '/home/weety/tart5/src/roscontrol/src/control_msgs/control_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::control_msgs::GripperCommandGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::control_msgs::GripperCommandGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::control_msgs::GripperCommandGoal_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "86fd82f4ddc48a4cb6856cfa69217e43";
  }

  static const char* value(const ::control_msgs::GripperCommandGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x86fd82f4ddc48a4cULL;
  static const uint64_t static_value2 = 0xb6856cfa69217e43ULL;
};

template<class ContainerAllocator>
struct DataType< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "control_msgs/GripperCommandGoal";
  }

  static const char* value(const ::control_msgs::GripperCommandGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
GripperCommand command\n\
\n\
================================================================================\n\
MSG: control_msgs/GripperCommand\n\
float64 position\n\
float64 max_effort\n\
";
  }

  static const char* value(const ::control_msgs::GripperCommandGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.command);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GripperCommandGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::control_msgs::GripperCommandGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::control_msgs::GripperCommandGoal_<ContainerAllocator>& v)
  {
    s << indent << "command: ";
    s << std::endl;
    Printer< ::control_msgs::GripperCommand_<ContainerAllocator> >::stream(s, indent + "  ", v.command);
  }
};

} // namespace message_operations
} // namespace ros

#endif // CONTROL_MSGS_MESSAGE_GRIPPERCOMMANDGOAL_H
