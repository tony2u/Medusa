local _M = globalclass(...);

require("Delegate")

function _M:ctor()
	self.handlers = { }
	self.disableCollectOnFire = nil;

	local metatable = getmetatable(self);
	metatable.__call = self.Invoke;
end

function _M:IsEmpty()
	return #self.handlers == 0;
end

function _M:Add(func, ...)
	local del = Delegate.new(func, ...);
	self.handlers[#self.handlers + 1] = del;
	return self;
end

function _M:Remove(func)
	local f = Delegate.new(func);
	for
		i, v in ipairs(self.handlers)
	do
		if v:EqualsWith(f) then
			table.remove(self.handlers, i);
			return true;
		end
	end
	return false;
end

function _M:CheckValid()
	if not self.disableCollectOnFire then
		collectgarbage();
	end
	while true do
		local isGot = false;
		for
			i, v in ipairs(self.handlers)
		do
			if not v:IsValid() then
				table.remove(self.handlers, i);
				isGot = true;
				break;
			end
		end

		if not isGot then
			break
		end
	end
end

function _M:Invoke(...)
	self:CheckValid();

	local results = { };
	for
		k, v in pairs(self.handlers)
	do
		results[#results + 1] = v:Invoke(...);
	end
	return table.unpack(results);
end
