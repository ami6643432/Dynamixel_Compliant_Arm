// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rft_sensor_serial:srv/RftOperation.idl
// generated code does not contain a copyright notice
#include "rft_sensor_serial/srv/detail/rft_operation__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
rft_sensor_serial__srv__RftOperation_Request__init(rft_sensor_serial__srv__RftOperation_Request * msg)
{
  if (!msg) {
    return false;
  }
  // op_type
  // param1
  // param2
  // param3
  return true;
}

void
rft_sensor_serial__srv__RftOperation_Request__fini(rft_sensor_serial__srv__RftOperation_Request * msg)
{
  if (!msg) {
    return;
  }
  // op_type
  // param1
  // param2
  // param3
}

bool
rft_sensor_serial__srv__RftOperation_Request__are_equal(const rft_sensor_serial__srv__RftOperation_Request * lhs, const rft_sensor_serial__srv__RftOperation_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // op_type
  if (lhs->op_type != rhs->op_type) {
    return false;
  }
  // param1
  if (lhs->param1 != rhs->param1) {
    return false;
  }
  // param2
  if (lhs->param2 != rhs->param2) {
    return false;
  }
  // param3
  if (lhs->param3 != rhs->param3) {
    return false;
  }
  return true;
}

bool
rft_sensor_serial__srv__RftOperation_Request__copy(
  const rft_sensor_serial__srv__RftOperation_Request * input,
  rft_sensor_serial__srv__RftOperation_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // op_type
  output->op_type = input->op_type;
  // param1
  output->param1 = input->param1;
  // param2
  output->param2 = input->param2;
  // param3
  output->param3 = input->param3;
  return true;
}

rft_sensor_serial__srv__RftOperation_Request *
rft_sensor_serial__srv__RftOperation_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rft_sensor_serial__srv__RftOperation_Request * msg = (rft_sensor_serial__srv__RftOperation_Request *)allocator.allocate(sizeof(rft_sensor_serial__srv__RftOperation_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rft_sensor_serial__srv__RftOperation_Request));
  bool success = rft_sensor_serial__srv__RftOperation_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rft_sensor_serial__srv__RftOperation_Request__destroy(rft_sensor_serial__srv__RftOperation_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rft_sensor_serial__srv__RftOperation_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rft_sensor_serial__srv__RftOperation_Request__Sequence__init(rft_sensor_serial__srv__RftOperation_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rft_sensor_serial__srv__RftOperation_Request * data = NULL;

  if (size) {
    data = (rft_sensor_serial__srv__RftOperation_Request *)allocator.zero_allocate(size, sizeof(rft_sensor_serial__srv__RftOperation_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rft_sensor_serial__srv__RftOperation_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rft_sensor_serial__srv__RftOperation_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rft_sensor_serial__srv__RftOperation_Request__Sequence__fini(rft_sensor_serial__srv__RftOperation_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rft_sensor_serial__srv__RftOperation_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rft_sensor_serial__srv__RftOperation_Request__Sequence *
rft_sensor_serial__srv__RftOperation_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rft_sensor_serial__srv__RftOperation_Request__Sequence * array = (rft_sensor_serial__srv__RftOperation_Request__Sequence *)allocator.allocate(sizeof(rft_sensor_serial__srv__RftOperation_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rft_sensor_serial__srv__RftOperation_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rft_sensor_serial__srv__RftOperation_Request__Sequence__destroy(rft_sensor_serial__srv__RftOperation_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rft_sensor_serial__srv__RftOperation_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rft_sensor_serial__srv__RftOperation_Request__Sequence__are_equal(const rft_sensor_serial__srv__RftOperation_Request__Sequence * lhs, const rft_sensor_serial__srv__RftOperation_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rft_sensor_serial__srv__RftOperation_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rft_sensor_serial__srv__RftOperation_Request__Sequence__copy(
  const rft_sensor_serial__srv__RftOperation_Request__Sequence * input,
  rft_sensor_serial__srv__RftOperation_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rft_sensor_serial__srv__RftOperation_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rft_sensor_serial__srv__RftOperation_Request * data =
      (rft_sensor_serial__srv__RftOperation_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rft_sensor_serial__srv__RftOperation_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rft_sensor_serial__srv__RftOperation_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rft_sensor_serial__srv__RftOperation_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
rft_sensor_serial__srv__RftOperation_Response__init(rft_sensor_serial__srv__RftOperation_Response * msg)
{
  if (!msg) {
    return false;
  }
  // result
  return true;
}

void
rft_sensor_serial__srv__RftOperation_Response__fini(rft_sensor_serial__srv__RftOperation_Response * msg)
{
  if (!msg) {
    return;
  }
  // result
}

bool
rft_sensor_serial__srv__RftOperation_Response__are_equal(const rft_sensor_serial__srv__RftOperation_Response * lhs, const rft_sensor_serial__srv__RftOperation_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result
  if (lhs->result != rhs->result) {
    return false;
  }
  return true;
}

bool
rft_sensor_serial__srv__RftOperation_Response__copy(
  const rft_sensor_serial__srv__RftOperation_Response * input,
  rft_sensor_serial__srv__RftOperation_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // result
  output->result = input->result;
  return true;
}

rft_sensor_serial__srv__RftOperation_Response *
rft_sensor_serial__srv__RftOperation_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rft_sensor_serial__srv__RftOperation_Response * msg = (rft_sensor_serial__srv__RftOperation_Response *)allocator.allocate(sizeof(rft_sensor_serial__srv__RftOperation_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rft_sensor_serial__srv__RftOperation_Response));
  bool success = rft_sensor_serial__srv__RftOperation_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rft_sensor_serial__srv__RftOperation_Response__destroy(rft_sensor_serial__srv__RftOperation_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rft_sensor_serial__srv__RftOperation_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rft_sensor_serial__srv__RftOperation_Response__Sequence__init(rft_sensor_serial__srv__RftOperation_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rft_sensor_serial__srv__RftOperation_Response * data = NULL;

  if (size) {
    data = (rft_sensor_serial__srv__RftOperation_Response *)allocator.zero_allocate(size, sizeof(rft_sensor_serial__srv__RftOperation_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rft_sensor_serial__srv__RftOperation_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rft_sensor_serial__srv__RftOperation_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rft_sensor_serial__srv__RftOperation_Response__Sequence__fini(rft_sensor_serial__srv__RftOperation_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rft_sensor_serial__srv__RftOperation_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rft_sensor_serial__srv__RftOperation_Response__Sequence *
rft_sensor_serial__srv__RftOperation_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rft_sensor_serial__srv__RftOperation_Response__Sequence * array = (rft_sensor_serial__srv__RftOperation_Response__Sequence *)allocator.allocate(sizeof(rft_sensor_serial__srv__RftOperation_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rft_sensor_serial__srv__RftOperation_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rft_sensor_serial__srv__RftOperation_Response__Sequence__destroy(rft_sensor_serial__srv__RftOperation_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rft_sensor_serial__srv__RftOperation_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rft_sensor_serial__srv__RftOperation_Response__Sequence__are_equal(const rft_sensor_serial__srv__RftOperation_Response__Sequence * lhs, const rft_sensor_serial__srv__RftOperation_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rft_sensor_serial__srv__RftOperation_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rft_sensor_serial__srv__RftOperation_Response__Sequence__copy(
  const rft_sensor_serial__srv__RftOperation_Response__Sequence * input,
  rft_sensor_serial__srv__RftOperation_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rft_sensor_serial__srv__RftOperation_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rft_sensor_serial__srv__RftOperation_Response * data =
      (rft_sensor_serial__srv__RftOperation_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rft_sensor_serial__srv__RftOperation_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rft_sensor_serial__srv__RftOperation_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rft_sensor_serial__srv__RftOperation_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
