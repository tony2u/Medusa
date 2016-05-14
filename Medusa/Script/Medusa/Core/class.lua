require("stringExtend")

function clone(object)
	local lookup_table = { }
	local function _copy(object)
		if type(object) ~= "table" then
			return object
		elseif lookup_table[object] then
			return lookup_table[object]
		end
		local new_table = { }
		lookup_table[object] = new_table
		for key, value in pairs(object) do
			new_table[_copy(key)] = _copy(value)
		end
		return setmetatable(new_table, getmetatable(object))
	end
	return _copy(object)
end

function class(name, base)
	local newClass = { };
	newClass.__name = name
	newClass.__index = newClass
	newClass.__class = newClass

	function newClass:__ctor(cls,...)
		if cls.__base then cls.__base.__ctor(self,cls.__base,...); end
		if cls.ctor then cls.ctor(self,...); end
	end

	function newClass.new(...)
		local instance = setmetatable( { }, newClass)
		instance:__ctor(newClass,...)
		return instance
	end

	function newClass.toclass(data)
		return setmetatable( data, newClass)
	end


	if not base then
		return newClass;
	end

	local baseType = type(base);
	if baseType == "table" then
		setmetatable(newClass, { __index = base });
		newClass.__base = base;
		return newClass;
	end

	if baseType == "function" then
		function newClass.new(...)
			local instance = base();
			setmetatable(instance, newClass)
			instance:__ctor(newClass,...)
			return instance
		end

		return newClass;
	end

end

function globalclass(name, super)
	local lastPart = string.LastPart(name);
	local _M = class(lastPart, super);
	_G[lastPart] = _M;
	package.loaded[name] = _M;	--only apply to require
	_M.__path = name;
	_M.__name = lastPart;
	_M.__dir = string.PrevPart(name);
	return _M;
end

function globaltable(name, super)
	local lastPart = string.LastPart(name);

	local _M = { };
	if super then
		if type(super) == "string" then
			super = require(super);
		end
		setmetatable(_M, {__index=super});
	end

	_G[lastPart] = _M;
	package.loaded[name] = _M;
	return _M;
end

function import(moduleName, currentModuleName)
	local currentModuleNameParts
	local moduleFullName = moduleName
	local offset = 1

	while true do
		if string.byte(moduleName, offset) ~= 46 then
			-- .
			moduleFullName = string.sub(moduleName, offset)
			if currentModuleNameParts and #currentModuleNameParts > 0 then
				moduleFullName = table.concat(currentModuleNameParts, ".") .. "." .. moduleFullName
			end
			break
		end
		offset = offset + 1

		if not currentModuleNameParts then
			if not currentModuleName then
				local n, v = debug.getlocal(3, 1)
				currentModuleName = v
			end

			currentModuleNameParts = string.split(currentModuleName, ".")
		end
		table.remove(currentModuleNameParts, #currentModuleNameParts)
	end

	return require(moduleFullName)
end
