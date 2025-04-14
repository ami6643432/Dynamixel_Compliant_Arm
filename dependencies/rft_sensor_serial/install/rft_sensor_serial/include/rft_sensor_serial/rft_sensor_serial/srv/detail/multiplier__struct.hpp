// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rft_sensor_serial:srv/Multiplier.idl
// generated code does not contain a copyright notice

#ifndef RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__STRUCT_HPP_
#define RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__rft_sensor_serial__srv__Multiplier_Request __attribute__((deprecated))
#else
# define DEPRECATED__rft_sensor_serial__srv__Multiplier_Request __declspec(deprecated)
#endif

namespace rft_sensor_serial
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Multiplier_Request_
{
  using Type = Multiplier_Request_<ContainerAllocator>;

  explicit Multiplier_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->a = 0l;
      this->b = 0l;
    }
  }

  explicit Multiplier_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->a = 0l;
      this->b = 0l;
    }
  }

  // field types and members
  using _a_type =
    int32_t;
  _a_type a;
  using _b_type =
    int32_t;
  _b_type b;

  // setters for named parameter idiom
  Type & set__a(
    const int32_t & _arg)
  {
    this->a = _arg;
    return *this;
  }
  Type & set__b(
    const int32_t & _arg)
  {
    this->b = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rft_sensor_serial__srv__Multiplier_Request
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rft_sensor_serial__srv__Multiplier_Request
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Multiplier_Request_ & other) const
  {
    if (this->a != other.a) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    return true;
  }
  bool operator!=(const Multiplier_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Multiplier_Request_

// alias to use template instance with default allocator
using Multiplier_Request =
  rft_sensor_serial::srv::Multiplier_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rft_sensor_serial


#ifndef _WIN32
# define DEPRECATED__rft_sensor_serial__srv__Multiplier_Response __attribute__((deprecated))
#else
# define DEPRECATED__rft_sensor_serial__srv__Multiplier_Response __declspec(deprecated)
#endif

namespace rft_sensor_serial
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Multiplier_Response_
{
  using Type = Multiplier_Response_<ContainerAllocator>;

  explicit Multiplier_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  explicit Multiplier_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = 0l;
    }
  }

  // field types and members
  using _result_type =
    int32_t;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const int32_t & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rft_sensor_serial__srv__Multiplier_Response
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rft_sensor_serial__srv__Multiplier_Response
    std::shared_ptr<rft_sensor_serial::srv::Multiplier_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Multiplier_Response_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const Multiplier_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Multiplier_Response_

// alias to use template instance with default allocator
using Multiplier_Response =
  rft_sensor_serial::srv::Multiplier_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace rft_sensor_serial

namespace rft_sensor_serial
{

namespace srv
{

struct Multiplier
{
  using Request = rft_sensor_serial::srv::Multiplier_Request;
  using Response = rft_sensor_serial::srv::Multiplier_Response;
};

}  // namespace srv

}  // namespace rft_sensor_serial

#endif  // RFT_SENSOR_SERIAL__SRV__DETAIL__MULTIPLIER__STRUCT_HPP_
