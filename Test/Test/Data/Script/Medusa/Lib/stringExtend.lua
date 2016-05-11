
function string.split(str, delimiter)
    if (delimiter=='') then return false end
    local pos,arr = 0, {}
    -- for each divider found
    for st,sp in function() return string.find(str, delimiter, pos, true) end do
        table.insert(arr, string.sub(str, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(str, pos))
    return arr
end

function string.ltrim(str)
    return string.gsub(str, "^[ \t\n\r]+", "")
end

function string.rtrim(str)
    return string.gsub(str, "[ \t\n\r]+$", "")
end

function string.trim(str)
    str = string.gsub(str, "^[ \t\n\r]+", "")
    return string.gsub(str, "[ \t\n\r]+$", "")
end


function string.LastPart(str)
	local index=1;
	while true
	do
		local begin,_= string.find(str,".",index,true);
		if begin then index=begin+1;else break;end
	end
	return string.sub(str,index);
end

function string.PrevPart(str)
	local index=1;
	while true
	do
		local begin,_= string.find(str,".",index,true);
		if begin then index=begin+1;else break;end
	end
	if index==1 then
		return str;
	else
		return string.sub(str,1,index-2);
	end
end


function string.CombinePart(str1,str2)
	return str1.."."..str2;
end
