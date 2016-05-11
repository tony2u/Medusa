require("Medusa.Medusa")
require("Game.HelloLuaGame")

local function __G__TRACKBACK__(msg)
  local msg = debug.traceback(msg, 3)
  print(msg)
  return msg
end

local function main()

end


local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    error(msg)
end
