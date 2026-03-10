--[[
  delta_example.lua
  Demonstrates the DeltaAPI plugin functions in the built Lua interpreter.
  All functions are stub implementations simulating a Delta robot controller API.
--]]

print("=== DeltaAPI Example Script ===")
print()

-- 1. Digital Input (DI)
print("-- Digital Input (DI) --")
local status = DI(1)
print(string.format("DI(1) = %s", tostring(status)))
local status_by_name = DI("sensor_A")
print(string.format("DI('sensor_A') = %s", tostring(status_by_name)))
local status_num = DI(1, 4)
print(string.format("DI(1, 4) = %d  (bit-field of 4 pins)", status_num))
print()

-- 2. Digital Output (DO)
print("-- Digital Output (DO) --")
DO(1, "ON")
print("DO(1, 'ON')  -> set pin 1 ON")
DO(2, "OFF")
print("DO(2, 'OFF') -> set pin 2 OFF")
DO(3, "ON", 0.5)
print("DO(3, 'ON', 0.5) -> set pin 3 ON, reverse after 0.5s")
DO(1, 3, 5)
print("DO(1, 3, 5) -> write bit-field 5 to pins 1-3")
print()

-- 3. External Board I/O
print("-- External Board I/O (ExtDI / ExtDO) --")
local ext_status = ExtDI(4, 1)
print(string.format("ExtDI(4, 1) = %s", tostring(ext_status)))
ExtDO(4, 1, "ON")
print("ExtDO(4, 1, 'ON')  -> external board 4, pin 1 ON")
ExtDO(4, 2, "ON", 1.0)
print("ExtDO(4, 2, 'ON', 1.0) -> with 1s delay")
print()

-- 4. Point & Motion
print("-- Point & Motion --")
SetGlobalPoint(1, "GL_P1", 200, 200, -100, 0, 0, 0, 0, 0, 0, 0, 0, {0,0,0,0,0,0,0,0})
print("SetGlobalPoint(1, 'GL_P1', ...) -> global point defined")
local x_val  = ReadPoint(1, "X")
local y_val  = ReadPoint(1, "Y")
local rz_val = ReadPoint(1, "RZ")
print(string.format("ReadPoint(1, 'X')  = %.1f mm", x_val))
print(string.format("ReadPoint(1, 'Y')  = %.1f mm", y_val))
print(string.format("ReadPoint(1, 'RZ') = %.1f deg", rz_val))
MovP(1)
print("MovP(1) -> PTP move to point 1")
MovL("GL_P1")
print("MovL('GL_P1') -> linear move to GL_P1")
MovJ(1, 90)
print("MovJ(1, 90) -> rotate joint 1 to 90 degrees")
print()

-- 5. Speed / Acceleration / Accuracy
print("-- Speed / Acceleration / Accuracy --")
SpdJ(50)
print("SpdJ(50)  -> joint speed 50%")
AccJ(30)
print("AccJ(30)  -> joint acceleration 30%")
DecJ(30)
print("DecJ(30)  -> joint deceleration 30%")
SpdL(500)
print("SpdL(500) -> linear speed 500 mm/s")
AccL(1000)
print("AccL(1000) -> linear acceleration 1000 mm/s^2")
DecL(1000)
print("DecL(1000) -> linear deceleration 1000 mm/s^2")
Accur("HIGH")
print("Accur('HIGH') -> in-place accuracy HIGH")
print()

-- 6. WAIT / DELAY
print("-- Timing: WAIT / DELAY --")
WAIT("DI", 1, "ON")
print("WAIT('DI', 1, 'ON') -> wait until DI pin 1 is ON")
WAIT("DO", 1, "ON", 1000)
print("WAIT('DO', 1, 'ON', 1000) -> wait up to 1000 ms")
DELAY(0.5)
print("DELAY(0.5) -> pause 0.5 seconds")
print()

-- 7. Modbus
print("-- Modbus: ReadModbus / WriteModbus --")
local reg_val = ReadModbus(0x1010, "DW")
print(string.format("ReadModbus(0x1010, 'DW') = %d", reg_val))
WriteModbus(0x1010, "DW", 42)
print("WriteModbus(0x1010, 'DW', 42) -> wrote 42")
local reg_val2 = ReadModbus(0x1010, "W")
print(string.format("ReadModbus(0x1010, 'W')  = %d", reg_val2))
print()

-- 8. Socket
print("-- Socket Communication --")
SocketVersion()
print("SocketVersion() -> (stub: no output)")
local retPort, retStatus, retErr = CheckAllStatus()
print(string.format("CheckAllStatus() -> ports=%s, statuses=%s, errors=%s",
  type(retPort), type(retStatus), type(retErr)))
local port, sock_status, err = CheckStatus()
print(string.format("CheckStatus() -> port=%d, status=%s, errcode=%d",
  port, sock_status, err))
local sock = SocketClass("192.168.1.99", 21, nil, "\r\n", nil, 0.3, 5)
print(string.format("SocketClass(...) -> type=%s", type(sock)))
print()

-- 9. Multi-task
print("-- Multi-task: AuxTasksAdd / AuxTasks --")
local task_log = {}
function MotionTask()
  MovP(1)
  MovP(2)
  table.insert(task_log, "MotionTask ran")
end
function OutputTask1()
  DO(1, "ON")
  DO(1, "OFF")
  table.insert(task_log, "OutputTask1 ran")
end
AuxTasksAdd(MotionTask, OutputTask1)
print("AuxTasksAdd(MotionTask, OutputTask1) -> tasks registered")
for i = 1, 3 do
  AuxTasks()
end
print(string.format("AuxTasks() called 3 times (stub: tasks not auto-invoked, task_log size=%d)", #task_log))
print()

-- 10. String split utility
print("-- String utility: split --")
local csv = "123,A1,B1,C2,D3"
local parts = split(csv, ",")
io.write("split('123,A1,B1,C2,D3', ',') -> ")
for i = 1, #parts do
  io.write(string.format("[%d]=%s ", i, parts[i]))
end
print()
local result2 = split("hello world foo", " ")
io.write("split('hello world foo', ' ') -> ")
for _, v in ipairs(result2) do
  io.write("[" .. v .. "] ")
end
print()
print()

-- 11. delta module table
print("-- Using 'delta' module table (require) --")
local delta = require("delta")
print(string.format("delta.DI(5) = %s", tostring(delta.DI(5))))
print(string.format("delta.ReadModbus(0x1000, 'W') = %d", delta.ReadModbus(0x1000, "W")))
print(string.format("delta.ExtDI(4, 2) = %s", tostring(delta.ExtDI(4, 2))))
print()

print("=== delta_example.lua completed successfully ===")
