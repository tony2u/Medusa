local _M = globalclass(...);

function _M:ctor(func, ...)
	local metatable = getmetatable(self);
	metatable.__call = self.Invoke;

	self.func = func;
	self.args = table.pack(...)
	setmetatable(self.args, { __mode = "v" });

end

function _M:EqualsWith(del)
	if del then
		return self.func == del.func;
	end
	return false;
end

function _M:Invoke(...)
	if not self:IsValid() then return end;

	if self.args and self.args.n > 0 then
		return self.func(table.unpack(self.args), ...);
	else
		return self.func(...);
	end
end

function _M:IsValid()
	local curArgCount = #self.args;
	return curArgCount == self.args.n;
end


function bind(func, ...)
	return _M.new(func, ...);
end

function handler(obj, method)
    return function(...)
        return method(obj, ...)
    end
end
