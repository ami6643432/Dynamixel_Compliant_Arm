from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='rft_sensor_serial',
            executable='rft_sensor_serial_node',
            name='rft_sensor_serial',
            parameters=[{
                'RFT_COM_PORT': '/dev/ttyUSB1', 
                'RFT_TORQUE_DIVIDER': 1000
            }]
        )
    ])