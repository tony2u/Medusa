local _M = globalclass(...,INode);
_M.currentEditorFileType = nil;
_M.autoEditor = true;
function _M:ctor(...)
	if self.currentEditorFileType and self.autoEditor then
		self.editorFile = self.__name .. self.currentEditorFileType;
	end
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
