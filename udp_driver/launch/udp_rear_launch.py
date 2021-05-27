import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.actions import Node
from launch_ros.actions import LifecycleNode
from launch.actions import EmitEvent
from launch.actions import LogInfo
from launch.actions import RegisterEventHandler
from launch_ros.events.lifecycle import ChangeState
from launch_ros.event_handlers import OnStateTransition
from launch_ros.descriptions import ComposableNode
from ament_index_python.packages import get_package_share_directory
from pathlib import Path
import yaml

import lifecycle_msgs.msg

def generate_launch_description():
    ld = launch.LaunchDescription()

    parameters_file_path = Path(get_package_share_directory('udp_driver'), 'params', 'rear.yaml')

    with open(parameters_file_path, 'r') as f:
        params = yaml.safe_load(f)['/**']['ros__parameters']
    
    i = 0
    for port in params['port']:
        udp_receiver_node = LifecycleNode(
            namespace = '',
            name = 'udp_receiver',
            package = 'udp_driver',
            executable = 'udp_receiver_node_exe',
            parameters = [
                {"ip": params['ip']},
                {"port": port},
                {"output_topic": params['output_topic'][i]}
            ],
            output = 'screen')

        # Make the udp_driver node take the 'configure' transition
        udp_receiver_configure_event = EmitEvent(
            event = ChangeState(
                lifecycle_node_matcher = launch.events.matches_action(udp_receiver_node),
                transition_id = lifecycle_msgs.msg.Transition.TRANSITION_CONFIGURE,
            )
        )
    
        udp_receiver_activate_event = EmitEvent(
            event = ChangeState(
                lifecycle_node_matcher = launch.events.matches_action(udp_receiver_node),
                transition_id = lifecycle_msgs.msg.Transition.TRANSITION_ACTIVATE,
             )
        )
        
        ld.add_action(udp_receiver_node)
        ld.add_action(udp_receiver_configure_event)
        ld.add_action(udp_receiver_activate_event)

        i += 1
    return ld
