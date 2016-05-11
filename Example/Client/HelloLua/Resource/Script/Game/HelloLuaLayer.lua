local _M = globalclass(...,ILayer);

function _M:ctor(id,id2)
	printf("%d %d",id,id2);
end

function _M:OnEnter()
	local node= NodeFactory.NewSprite("test.png");
	self:Node():AddChild(node);
	return true;
end
