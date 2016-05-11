local _M = globalclass(...);

function _M:ctor()
	self.items = { }
end

function _M:Recycle(id, val)
	local itemList = self.items[id];
	if not itemList then
		itemList = { };
		self.items[id] = itemList;
	end
	itemList[#itemList + 1] = val;
end

function _M:Create(id)
	local itemList = self.items[id];
	if itemList then
		local last = itemList[#itemList];
		if last then
			itemList[#itemList] = nil;
		end
		return last;
	end
end

function _M:ReleaseAll(func)
	if func then
		for _, itemList in pairs(self.items) do
			for _, item in pairs(itemList) do
				func(item);
			end
		end
	end

	self.items = { }
end