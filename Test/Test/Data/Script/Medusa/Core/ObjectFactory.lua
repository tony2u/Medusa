local _M = globalclass(...);

function _M:ctor()
	self.items = { }
end

function _M:Register(id, val)
	self.items[id] = val;
end

function _M:RegisterItems(items)
	for id, item in pairs(items) do
		self.items[id] = item;
	end
end

function _M:UnRegister(id)
	self.items[id] = nil;
end

function _M:Get(id)
	return self.items[id];
end


function _M:Create(id, ...)
	local item = self.items[id];
	if item then
		return item.new(...);
	end
end

return _M;
