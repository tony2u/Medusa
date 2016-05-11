
if _VERSION == 'Lua 5.1' then
	if not table.pack then
		function table.pack(...)
			return { n = select('#', ...); ...}
		end
	end

	if not table.unpack then
		table.unpack = unpack;
	end

end

--[[--

insert list.

**Usage:**

    local dest = {1, 2, 3}
    local src  = {4, 5, 6}
    table.insertList(dest, src)
    -- dest = {1, 2, 3, 4, 5, 6}
	dest = {1, 2, 3}
	table.insertList(dest, src, 5)
    -- dest = {1, 2, 3, nil, 4, 5, 6}


@param table dest
@param table src
@param table beginPos insert position for dest
]]
function table.insertList(dest, src, beginPos)
	beginPos = trynumber(beginPos)
	if beginPos == nil then
		beginPos = #dest + 1
	end

	local len = #src
	for i = 0, len - 1 do
		dest[i + beginPos] = src[i + 1]
	end
end

function table.isset(hashtable, key)
    local t = type(hashtable)
    return (t == "table" or t == "userdata") and hashtable[key] ~= nil
end

function table.count(t)
    local count = 0
    for k, v in pairs(t) do
        count = count + 1
    end
    return count
end

function table.keys(hashtable)
    local keys = {}
    for k, v in pairs(hashtable) do
        keys[#keys + 1] = k
    end
    return keys
end

function table.values(hashtable)
    local values = {}
    for k, v in pairs(hashtable) do
        values[#values + 1] = v
    end
    return values
end

function table.merge(dest, src)
    for k, v in pairs(src) do
        dest[k] = v
    end
end


function table.indexOf(list, target, from, useMaxN)
	local len =(useMaxN and #list) or table.maxn(list)
	if from == nil then
		from = 1
	end
	for i = from, len do
		if list[i] == target then
			return i
		end
	end
	return -1
end

function table.indexOfKey(list, key, value, from, useMaxN)
	local len =(useMaxN and #list) or table.maxn(list)
	if from == nil then
		from = 1
	end
	local item = nil
	for i = from, len do
		item = list[i]
		if item ~= nil and item[key] == value then
			return i
		end
	end
	return -1
end

function table.removeItem(list, item, removeAll)
	local rmCount = 0
	for i = 1, #list do
		if list[i - rmCount] == item then
			table.remove(list, i - rmCount)
			if removeAll then
				rmCount = rmCount + 1
			else
				break
			end
		end
	end
end

function table.keyof(hashtable, value)
    for k, v in pairs(hashtable) do
        if v == value then return k end
    end
    return nil
end

function table.removebyvalue(array, value, removeall)
    local c, i, max = 0, 1, #array
    while i <= max do
        if array[i] == value then
            table.remove(array, i)
            c = c + 1
            i = i - 1
            max = max - 1
            if not removeall then break end
        end
        i = i + 1
    end
    return c
end

function table.map(t, fn)
    for k, v in pairs(t) do
        t[k] = fn(k, v)
    end
end

function table.each(t, fn)
    for k,v in pairs(t) do
        fn(k, v)
    end
end

function table.filter(t, fn)
    for k, v in pairs(t) do
        if not fn(k, v) then t[k] = nil end
    end
end
