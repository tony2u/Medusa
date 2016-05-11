module(..., package.seeall);
local extend=require("ISceneExtend");

function Push(className, flags, ...)
	className = className or "";
	flags = flags or 0;
	local native = nil;
	local scriptObject = nil;

	if type(className) == "table" then
		return _M.PushEx("", "", className, flags, ...);
	else
		if (FileSystem.ExistsLua(className)) then
			return _M.PushEx("", "", className, flags, ...);
		end

		local native= ml.SceneManager.Push(className, flags);
		extend.Apply(native);
		return native;
	end
end

function PushEx(className, editorFile, scriptFile, flags, ...)
	className = className or "";
	editorFile = editorFile or "";
	scriptFile = scriptFile or "";
	flags = flags or 0;
	local native = ml.SceneFactory.Create(className, editorFile);
	extend.Apply(native);
	local scriptObject = nil;

	if type(scriptFile) == "table" then
		scriptObject = scriptFile.new(...);
	else
		if scriptFile ~= "" then
			if (FileSystem.ExistsLua(scriptFile)) then
				scriptObject = require(scriptFile).new(...);
			else
				error("Cannot find script file:%s", scriptFile);
			end
		end
	end
	print(native:__tostring());
	native:SetScriptObject(scriptObject);

	ml.SceneManager.PushObject(native, flags);

	return native;
end