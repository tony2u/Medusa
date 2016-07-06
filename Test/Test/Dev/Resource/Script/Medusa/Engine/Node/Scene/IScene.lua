local _M = globalclass(..., INode);

function _M:ctor(...)
		self.__editorFile = self.__name;	--set __editorFile to nil to disable editor
		self.__className=nil;	--set __className to create C++ object with this name
end

return _M;
