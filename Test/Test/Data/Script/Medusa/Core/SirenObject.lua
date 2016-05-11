local _M = globalclass(...);
require "Siren"

function _M:ctor()
	self.protoType=Siren.FindType(self.__name);
end

function _M:Serialize()
	return Siren.DeserializeTo(self.protoType,self);
end


function _M:Deserialize(data)
	return Siren.DeserializeTo(self,self.protoType,data);
end
