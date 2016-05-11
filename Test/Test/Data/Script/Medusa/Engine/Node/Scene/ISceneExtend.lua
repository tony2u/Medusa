local _M = { }

function _M.Push(obj, className, flags, ...)

	className = className or "";
	flags = flags or 0;
	local native = nil;
	local scriptObject = nil;

	if type(className) == "table" then
		return _M.PushEx(obj, "", "", className, flags, ...);
	else
		if (FileSystem.ExistsLua(className)) then
			return _M.PushEx(obj, "", "", className, flags, ...);
		end

		return obj:PushName(className, flags);
	end
end

function _M.PushEx(obj, className, editorFile, scriptFile, flags, ...)
	className = className or "";
	editorFile = editorFile or "";
	scriptFile = scriptFile or "";
	flags = flags or 0;

	local scriptObject = nil;
	if type(scriptFile) == "table" then
		scriptObject = scriptFile.new(...);
	else
		if scriptFile ~= "" then
			if (FileSystem.ExistsLua(scriptFile)) then
				scriptObject = require(scriptFile).new(...);
			else
				error("Cannot find script file:%s", scriptFile);
				return;
			end
		end
	end

	className=scriptObject.className or className;
	editorFile=scriptObject.editorFile or editorFile;
	local native = ml.LayerFactory.Create(className, editorFile);
	native:SetScriptObject(scriptObject);
	obj:PushObject(native, flags);

	return native;
end


function _M.Apply(val)
	local meta = getmetatable(val);
	meta.Push = _M.Push;
	meta.PushEx = _M.PushEx;
end

return _M;