local _M = globalclass(...,INode);

function _M:ctor(...)
	self.__base.ctor(self,...);
end

function _M:Start()
	
	return true;
end

function _M:Stop()
	return true;
end

function _M:Update(dt)
	print(string.format("Update %f", dt));
	return true;
end
