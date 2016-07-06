module(...,package.seeall);

function ExistsLua(file)
	return ml.FileSystem.Exists(file..".lua");
end
return _M;
