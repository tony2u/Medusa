local _M = globalclass(...);


function _M:ctor()

end

function _M:Start(val)
	--local scene=SceneManager.Push("HelloLuaScene",ScenePushFlags.None,12,56);

	local scene=SceneManager.Push("",ScenePushFlags.None,12,56);
	local layer=scene:Push("",LayerPushFlags.None,44,23);
	local sprite=NodeFactory.NewSprite("test.png");
	layer:AddChild(sprite);
	--local s=sprite:__tostring();

	--local is=ml.FileSystem.Exists("HelloLuaGame.lua");

	--SceneManager.Push("HelloWorldScene2","",0,1,2);
	--SceneManager:Push("HelloWorldScene",ScenePushFlags.None,1,2);

--	local scene=SceneManager:Push("HelloWorldScene")
--	local layer=scene:PushLayer("HelloLuaLayer");
--	local node= NodeFactory:CreateQuadSprite("test.png");
--	layer:AddChild(node);

	return true;
end

function _M:Stop()
	print("Stop");
	return true;
end

function _M:Update(dt)
	print(string.format("Update %f", dt));
	return true;
end
