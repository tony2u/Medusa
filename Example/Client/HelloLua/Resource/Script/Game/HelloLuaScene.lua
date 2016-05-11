local _M = globalclass(...,IScene);

function _M:ctor(id,id2)
	
end

function _M:OnEnter()
	self:Node():Push("HelloLuaLayer",LayerPushFlags.None,44,23);
--	self:PushLayer("HelloLuaLayer","HelloLuaLayer.csb",123,11);
	return true;
end

