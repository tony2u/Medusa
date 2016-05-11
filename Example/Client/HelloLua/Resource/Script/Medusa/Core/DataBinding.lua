local _M = globalclass(...);

function _M:ctor()
	self.parent = nil;
	self.event = Event.new();
	self.isEnabled = true;
end

function _M:IsEnabled()
	return self.isEnabled;
end

function _M:Enable(val)
	self.isEnabled = val;
end

function _M:Parent()
	return self.parent;
end

function _M:SetParent(val)
	self.parent = val;
end

function _M:Pause()
	local prev = self.isEnabled;
	self:Enable(false);
	return prev;
end

function _M:Resume(val)
	self:Enable(val);
end

function _M:BindTo(...)
	self.event:Add(...);
	return self;
end

function _M:Unbind(func)
	self.event:Remove(func);
end

function _M:FireEvent(...)
	self.event:Invoke(...);

	if self.parent then
		self.parent:FireEvent(...);
	end
end
