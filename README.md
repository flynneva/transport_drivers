# transport_drivers

A set of ROS2 drivers for transport-layer protocols. Currently utilizes the stand-alone ASIO library for most transport-layer functionality.

## Supported Drivers:

* **UDP Driver**

A package which encapsulates basic receving and sending of udp data.

Provided within this package are the following executabes:
- udp_receiver_node_exe: can receive UDP data
- udp_sender_node_exe: can send UDP data asynchronosouly
- udp_bridge_node_exe: combined both receiver and sender nodes into one

Provided within this package also is a `udp_driver` library without the ROS2 dependencies which could be used elsewhere.
    
* **Serial Driver**

A package which which encapsulates basic receiving and sending of serial data.

Provided within this package is the following executabe:
- serial_bridge: combined both receiver and sender nodes into one

Provided within this package also is a `serial_driver` library without the ROS2 dependencies which could be used elsewhere.

* **IO Context**

A library to write synchronous and asynchronous networking applications.


## Quick start

Clone the repo into your workspace, normally with the structure `workspace/src/<clone-repo-here>`:

```
git clone https://github.com/ros-drivers/transport_drivers.git
```

Install dependencies using `rosdep` from your top-level workspace directory:

```
rosdep install --from-paths src --ignore-src -r -y
```

## Testing

Comprehensive unit tests have been written for every package within this repository.

To run them yourself, use the normal command from your top-level workspace directory:

```
colcon test
```
