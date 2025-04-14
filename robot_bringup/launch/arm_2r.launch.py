import datetime
import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument, 
    RegisterEventHandler, 
    Shutdown, 
    SetEnvironmentVariable, 
    IncludeLaunchDescription,
    TimerAction
)
from launch.conditions import IfCondition, UnlessCondition
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, LaunchConfiguration, PathJoinSubstitution, AndSubstitution, NotSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node
from launch_ros.descriptions import ParameterValue


def generate_launch_description():
    # Declare arguments
    declared_arguments = [
        DeclareLaunchArgument('use_sim_time', default_value='False', description='Launch in simulation mode.'),
        DeclareLaunchArgument('namespace', default_value='', description='Namespace for the robot'),
        DeclareLaunchArgument('record', default_value='False', description='Record in ROS bag'),
        DeclareLaunchArgument('use_asmc', default_value='False', description='Use ASMC in JTC'),
        DeclareLaunchArgument('use_rviz', default_value='False', description='Launch RVIZ on startup'),
        DeclareLaunchArgument('use_effort', default_value='False', description='Use effort controller instead of JTC/ASMC'),
        SetEnvironmentVariable('RCUTILS_COLORIZED_OUTPUT', '1')
    ]
    
    declared_arguments.append(
        DeclareLaunchArgument(
            'use_impedance',
            default_value='false',
            description='Use impedance controller instead of PID or ASMC'
        )
    )

    # Initialize Arguments
    use_sim_time = LaunchConfiguration('use_sim_time')
    namespace = LaunchConfiguration('namespace')
    record = LaunchConfiguration('record')
    use_asmc = LaunchConfiguration('use_asmc')
    use_rviz = LaunchConfiguration('use_rviz')
    use_effort = LaunchConfiguration('use_effort')
    use_impedance = LaunchConfiguration('use_impedance')

    # Package Path
    package_path = get_package_share_directory('robot_bringup')

    # Get URDF via xacro
    xacro_path = PathJoinSubstitution([package_path, 'urdf', 'arm_2r.urdf.xacro'])

    # Set the robot controller file based on the mode
    robot_controllers_default = PathJoinSubstitution([package_path, 'config', 'arm_2r.yaml'])
    robot_controllers_asmc = PathJoinSubstitution([package_path, 'config', 'arm_2r_asmc.yaml'])
    robot_controllers_effort = PathJoinSubstitution([package_path, 'config', 'arm_2r_effort.yaml'])
    robot_controllers_impedance = PathJoinSubstitution([package_path, 'config', 'arm_2r_impedance.yaml'])
    
    # Robot State Publisher
    robot_state_pub_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        namespace=namespace,
        parameters=[
            {'use_sim_time': use_sim_time},
            {'robot_description': ParameterValue(
                Command(['xacro ', xacro_path, ' USE_WITH_SIM:=', use_sim_time]), value_type=str
            )}
        ]
    )

    # Controller Manager Node
    control_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        namespace=namespace,
        parameters=[
            {'use_sim_time': use_sim_time},
            robot_controllers_impedance if use_impedance else 
            (robot_controllers_effort if use_effort else
             (robot_controllers_asmc if use_asmc else robot_controllers_default)),
            # Path to RFT sensor parameters
            os.path.join(package_path, 'params', 'rft_params.yaml')
        ],
        output='both',
        remappings=[('~/robot_description', 'robot_description')],
        on_exit=Shutdown()
    )

    # Joint State Broadcaster with delayed start
    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        namespace=namespace,
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=[
            'joint_state_broadcaster',
            '--controller-manager', 'controller_manager',
            '--controller-manager-timeout', '60'  # Increased timeout
        ]
    )

    # Add delay before spawning joint state broadcaster
    delayed_joint_state_broadcaster = TimerAction(
        period=2.0,  # 2 second delay
        actions=[joint_state_broadcaster_spawner]
    )

    # Effort Controller Spawner
    arm_2r_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        namespace=namespace,
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=[
            'arm_2r_controller',
            '--controller-manager', 'controller_manager',
            '--controller-manager-timeout', '60'  # Increased timeout
        ],
        condition=UnlessCondition(use_impedance)  # Only spawn if NOT using impedance
    )

    # Delay arm controller spawn with additional fixed delay
    delay_arm_2r_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[
                TimerAction(
                    period=2.0,  # 2 second delay after joint state broadcaster
                    actions=[arm_2r_controller_spawner]
                )
            ]
        ),
        condition=UnlessCondition(use_impedance)  # Only spawn if NOT using impedance
    )
    
    
    # Impedance Effort Controller Spawner
    impedance_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        namespace=namespace,
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=[
            'arm_2r_impedance_controller',
            '--controller-manager', 'controller_manager',
            '--controller-manager-timeout', '60'
        ],
        condition=IfCondition(use_impedance)  # Only spawn if using impedance
    )

    # Add delay handler
    delay_impedance_controller_spawner = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[
                TimerAction(
                    period=1.0,
                    actions=[impedance_controller_spawner]
                )
            ]
        ),
        condition=IfCondition(use_impedance)  # Only spawn if using impedance
    )

    # Gazebo
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(get_package_share_directory('ros_gz_sim'), 'launch', 'gz_sim.launch.py')]
        ),
        launch_arguments=[('gz_args', '-r -v 4 empty.sdf')],
        condition=IfCondition(use_sim_time)
    )

    # ROS-Gazebo Bridge
    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        namespace=namespace,
        output='screen',
        parameters=[{'use_sim_time': use_sim_time}],
        condition=IfCondition(use_sim_time),
        arguments=['/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock]']
    )

    # RViz
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='log',
        namespace=namespace,
        parameters=[{'use_sim_time': use_sim_time}],
        arguments=['-d', os.path.join(package_path, 'rviz', 'arm_2r.rviz')],
        on_exit=Shutdown(),
        condition=IfCondition(use_rviz)
    )

    # Delay RViz start
    delay_rviz_after_joint_state_broadcaster = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=joint_state_broadcaster_spawner,
            on_exit=[
                TimerAction(
                    period=1.0,  # 1 second delay
                    actions=[rviz_node]
                )
            ]
        )
    )

    # ROS Bag Recorder
    rosbag_recorder_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [package_path, 'launch', 'rosbag_recorder.launch.py']
        ),
        launch_arguments={'use_sim_time': use_sim_time}.items(),
        condition=IfCondition(record)
    )

    # Return Launch Description with sequenced startup
    return LaunchDescription(
        declared_arguments + [
            # Start these first
            robot_state_pub_node,
            control_node,
            
            # Then joint state broadcaster after a delay
            delayed_joint_state_broadcaster,
            
            # Either run standard controller or impedance controller based on flag
            delay_arm_2r_controller_spawner,
            delay_impedance_controller_spawner,
            
            # Optional components
            delay_rviz_after_joint_state_broadcaster,
            gazebo,
            bridge,
            rosbag_recorder_launch
        ]
    )