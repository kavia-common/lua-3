--[[
  delta_example.lua — exercises Delta API bindings in DRASim Lua node.
  Run:  ros2 run drasim_lua lua_node --ros-args -p script_path:=$(pwd)/scripts/delta_example.lua
--]]
print("DRASim Delta API example starting...")

SpdJ(10); AccJ(10); DecJ(10)
SpdL(100); AccL(10); DecL(10)

SetGlobalPoint(1, "GL_P1", 200.0, 200.0, -100.0, 0.0, 0.0, 0.0)
SetGlobalPoint(2, "GL_P2", 300.0, 100.0, -100.0, 0.0, 0.0, 0.0)

local di1 = DI(1)
print("DI pin 1 = " .. di1)

DO(1, "ON", 0.5)

WriteModbus(0x1000, "W", 42)
local val = ReadModbus(0x1000, "W")
print("Modbus 0x1000 = " .. tostring(val))

MovJ(1, 45.0)
MovP("GL_P1")
MovL("GL_P2")

local parts = split("A,B,C", ",")
print("split: " .. parts[1] .. ", " .. parts[2] .. ", " .. parts[3])

print("Done.")
