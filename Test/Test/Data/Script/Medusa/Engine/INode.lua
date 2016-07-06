local _M = globalclass(...);
function _M:ctor()
	self.___node=nil;
end

function _M:Node()
	return self.___node;
end

function _M:SetNode(val)
	self.___node=val;
end


function _M:Enter()
	return self:OnEnter();
end

function _M:Exit()
	return self:OnExit();
end

function _M:Update(dt)
	return self:OnUpdate(dt);
end

function _M:UpdateLogic()
	return self:OnUpdateLogic();
end

function _M:ResetLogic()
	return self:OnResetLogic();
end

function _M:HandlerEvent(sender,e)
	return self:OnEvent(sender,e);
end


function _M:OnEnter()
	return true;
end

function _M:OnExit()
	return true;
end

function _M:OnUpdate(dt)
	return true;
end


function _M:OnUpdateLogic()
	return true;
end

function _M:OnResetLogic()
	return true;
end

function _M:OnEvent(sender,e)
	return true;
end

return _M;
