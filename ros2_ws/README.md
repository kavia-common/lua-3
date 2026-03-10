# DRASim ROS2 Humble Workspace

C++-only ROS2 Humble colcon workspace implementing a DRASim-style robot controller emulator.

## Packages

| Package | Purpose |
|---|---|
| `drasim_interfaces` | ROS2 msg/srv definitions |
| `drasim_core` | MemoryImage + IO/Modbus mapping (single source of truth) |
| `drasim_io_ros` | ROS2 node publishing IO state and providing services |
| `drasim_modbus` | Modbus/TCP server skeleton bound to MemoryImage |
| `drasim_lua` | Embedded Lua 5.4 interpreter + Delta API C++ bindings |
| `drasim_robot_emulator` | Motion emulator skeleton (MovJ / MovL / MovP) |

## Build

```bash
cd lua-3/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
source install/setup.bash
```

## Running nodes

```bash
ros2 run drasim_io_ros io_node
ros2 run drasim_modbus modbus_node
ros2 run drasim_lua lua_node
ros2 run drasim_robot_emulator robot_emulator_node
```

## Notes

- Parsers for `UserIO.dio` and `LPT.bin` are stubs in `drasim_core/src/parsers_*`.
- The Lua node embeds Lua 5.4 sources from the repo root.
- Target ROS2 distro: **Humble Hawksbill**
