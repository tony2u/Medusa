module(...,package.seeall);
require("SirenObject");

function FindAssembly(name)
	return ml.SirenMachine.FindAssembly(name);
end

function NewAssembly(name)
	return ml.SirenMachine.NewAssembly(name);
end

function LoadAssembly(file)
	return ml.SirenMachine.LoadAssembly(file);
end

function FindType(name)
	return ml.SirenMachine.FindType(name);
end

function Serialize(type,obj)
	return ml.Siren.Serialize(type,obj);
end

function Deserialize(type,data)
	return ml.Siren.Deserialize(type,data);
end

function DeserializeTo(obj,type,data)
	return ml.Siren.DeserializeTo(obj,type,data);
end
