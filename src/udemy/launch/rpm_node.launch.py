from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="udemy",
            executable="rpm",
            name="rpmpub",
            parameters=[
                {"rpm_val":5.0}
            ]
        ),
        Node(
            package="udemy",
            executable="speed",
            name="speedsub",
            parameters=[
                {"speed_val": 15 /100}
            ]
        ), 
    
        ExecuteProcess(
            cmd=['ros2', 'topic', 'echo', '/rpm'],
            output='screen'
        )
    ])