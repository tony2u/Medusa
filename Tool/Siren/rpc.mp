class LoginRequest[SuppressCopy,SuppressCompare,Dir=Core/rpc]
{
   string name;
};

class LoginResponse[SuppressCopy,SuppressCompare,Dir=Core/rpc]
{
   int error;
};

rpc ServiceName[Dir=Core/rpc]
{
	string GetName();
	int,float TestMultipleResult(int,float);
	List<int> TestMultipleResult2(int,string);
	int Login(LoginRequest);
	LoginResponse Login2(LoginRequest);
	LoginResponse Login3(string );
};