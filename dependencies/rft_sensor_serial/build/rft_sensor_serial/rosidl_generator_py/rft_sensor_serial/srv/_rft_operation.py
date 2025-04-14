# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rft_sensor_serial:srv/RftOperation.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RftOperation_Request(type):
    """Metaclass of message 'RftOperation_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rft_sensor_serial')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rft_sensor_serial.srv.RftOperation_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__rft_operation__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__rft_operation__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__rft_operation__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__rft_operation__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__rft_operation__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RftOperation_Request(metaclass=Metaclass_RftOperation_Request):
    """Message class 'RftOperation_Request'."""

    __slots__ = [
        '_op_type',
        '_param1',
        '_param2',
        '_param3',
    ]

    _fields_and_field_types = {
        'op_type': 'uint8',
        'param1': 'uint8',
        'param2': 'uint8',
        'param3': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.op_type = kwargs.get('op_type', int())
        self.param1 = kwargs.get('param1', int())
        self.param2 = kwargs.get('param2', int())
        self.param3 = kwargs.get('param3', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.op_type != other.op_type:
            return False
        if self.param1 != other.param1:
            return False
        if self.param2 != other.param2:
            return False
        if self.param3 != other.param3:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def op_type(self):
        """Message field 'op_type'."""
        return self._op_type

    @op_type.setter
    def op_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'op_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'op_type' field must be an unsigned integer in [0, 255]"
        self._op_type = value

    @builtins.property
    def param1(self):
        """Message field 'param1'."""
        return self._param1

    @param1.setter
    def param1(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'param1' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'param1' field must be an unsigned integer in [0, 255]"
        self._param1 = value

    @builtins.property
    def param2(self):
        """Message field 'param2'."""
        return self._param2

    @param2.setter
    def param2(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'param2' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'param2' field must be an unsigned integer in [0, 255]"
        self._param2 = value

    @builtins.property
    def param3(self):
        """Message field 'param3'."""
        return self._param3

    @param3.setter
    def param3(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'param3' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'param3' field must be an unsigned integer in [0, 255]"
        self._param3 = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_RftOperation_Response(type):
    """Metaclass of message 'RftOperation_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rft_sensor_serial')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rft_sensor_serial.srv.RftOperation_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__rft_operation__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__rft_operation__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__rft_operation__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__rft_operation__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__rft_operation__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RftOperation_Response(metaclass=Metaclass_RftOperation_Response):
    """Message class 'RftOperation_Response'."""

    __slots__ = [
        '_result',
    ]

    _fields_and_field_types = {
        'result': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.result = kwargs.get('result', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.result != other.result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def result(self):
        """Message field 'result'."""
        return self._result

    @result.setter
    def result(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'result' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'result' field must be an unsigned integer in [0, 255]"
        self._result = value


class Metaclass_RftOperation(type):
    """Metaclass of service 'RftOperation'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rft_sensor_serial')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rft_sensor_serial.srv.RftOperation')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__rft_operation

            from rft_sensor_serial.srv import _rft_operation
            if _rft_operation.Metaclass_RftOperation_Request._TYPE_SUPPORT is None:
                _rft_operation.Metaclass_RftOperation_Request.__import_type_support__()
            if _rft_operation.Metaclass_RftOperation_Response._TYPE_SUPPORT is None:
                _rft_operation.Metaclass_RftOperation_Response.__import_type_support__()


class RftOperation(metaclass=Metaclass_RftOperation):
    from rft_sensor_serial.srv._rft_operation import RftOperation_Request as Request
    from rft_sensor_serial.srv._rft_operation import RftOperation_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
