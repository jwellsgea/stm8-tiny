--[[
luarocks install periphery
luarocks install luacrc16
]]

local serial_path = arg[1]
local file = arg[2]

local crc = require 'crc16'

local Serial = require 'periphery'.Serial
local serial = Serial(serial_path, 230400)

-- enter boot loader

-- flash the shit

-- need
